namespace mc
{
SpectrumSource::SpectrumSource() : Thread("SpectrumSource") { }

auto SpectrumSource::addAudioData(juce::AudioBuffer<float> const& buffer, int startChannel, int numChannels) -> void
{
    if (abstractFifo_.getFreeSpace() < buffer.getNumSamples()) { return; }

    int start1 {};
    int block1 {};
    int start2 {};
    int block2 {};
    abstractFifo_.prepareToWrite(buffer.getNumSamples(), start1, block1, start2, block2);
    audioFifo_.copyFrom(0, start1, buffer.getReadPointer(startChannel), block1);
    if (block2 > 0) { audioFifo_.copyFrom(0, start2, buffer.getReadPointer(startChannel, block1), block2); }

    for (int channel = startChannel; channel < startChannel + numChannels; ++channel)
    {
        if (block1 > 0) { audioFifo_.addFrom(0, start1, buffer.getReadPointer(channel), block1); }
        if (block2 > 0) { audioFifo_.addFrom(0, start2, buffer.getReadPointer(channel, block1), block2); }
    }
    abstractFifo_.finishedWrite(block1 + block2);
    waitForData_.signal();
}

auto SpectrumSource::setupAnalyser(int const audioFifoSize, double const sampleRateToUse) -> void
{
    sampleRate_ = static_cast<float>(sampleRateToUse);
    audioFifo_.setSize(1, audioFifoSize);
    abstractFifo_.setTotalSize(audioFifoSize);
    fftBuffer_.setSize(1, fft_.getSize() * 2);
    averager_.setSize(5, fft_.getSize() / 2, false, true);

    startThread(5);
}

auto SpectrumSource::createPath(juce::Path& p, juce::Rectangle<float> const& bounds, float const minFreq) -> void
{
    p.clear();

    juce::ScopedLock lockedForReading(pathCreationLock_);
    const auto* fftData = averager_.getReadPointer(0);
    const auto factor   = bounds.getWidth() / 10.0f;

    p.startNewSubPath(bounds.getX() + factor * indexToX(0, minFreq), binToY(fftData[0], bounds));
    p.preallocateSpace(averager_.getNumSamples());
    auto lastX = -100.0;
    for (int i = 0; i < averager_.getNumSamples(); ++i)
    {
        const auto x = bounds.getX() + factor * indexToX(static_cast<float>(i), minFreq);
        const auto y = binToY(fftData[i], bounds);
        if (lastX + 6 < x)
        {
            p.lineTo(static_cast<float>(x), static_cast<float>(y));
            lastX = x;
        }
    }
}

auto SpectrumSource::checkForNewData() -> bool
{
    auto const available = newDataAvailable_.load();
    newDataAvailable_.store(false);
    return available;
}

auto SpectrumSource::run() -> void
{
    while (!threadShouldExit())
    {
        if (abstractFifo_.getNumReady() >= fft_.getSize())
        {
            fftBuffer_.clear();

            auto start1 = 0;
            auto block1 = 0;
            auto start2 = 0;
            auto block2 = 0;

            abstractFifo_.prepareToRead(fft_.getSize(), start1, block1, start2, block2);
            if (block1 > 0) { fftBuffer_.copyFrom(0, 0, audioFifo_.getReadPointer(0, start1), block1); }
            if (block2 > 0) { fftBuffer_.copyFrom(0, block1, audioFifo_.getReadPointer(0, start2), block2); }
            abstractFifo_.finishedRead(block1 + block2);

            windowing_.multiplyWithWindowingTable(fftBuffer_.getWritePointer(0), size_t(fft_.getSize()));
            fft_.performFrequencyOnlyForwardTransform(fftBuffer_.getWritePointer(0));

            juce::ScopedLock lockedForWriting(pathCreationLock_);
            averager_.addFrom(0, 0, averager_.getReadPointer(averagerPtr_), averager_.getNumSamples(), -1.0f);
            averager_.copyFrom(averagerPtr_, 0, fftBuffer_.getReadPointer(0), averager_.getNumSamples(),
                               1.0f / (averager_.getNumSamples() * (averager_.getNumChannels() - 1)));
            averager_.addFrom(0, 0, averager_.getReadPointer(averagerPtr_), averager_.getNumSamples());
            if (++averagerPtr_ == averager_.getNumChannels()) { averagerPtr_ = 1; }

            newDataAvailable_.store(true);
        }

        if (abstractFifo_.getNumReady() < fft_.getSize()) { waitForData_.wait(100); }
    }
}

auto SpectrumSource::indexToX(float const index, float const minFreq) const -> float
{
    const auto freq = (sampleRate_ * index) / fft_.getSize();
    return (freq > 0.01f) ? std::log(freq / minFreq) / std::log(2.0f) : 0.0f;
}

auto SpectrumSource::binToY(float const bin, juce::Rectangle<float> const& bounds) -> float
{
    auto const infinity   = -60.0f;
    auto const topPadding = bounds.getHeight() * 0.05f;
    auto const db         = juce::Decibels::gainToDecibels(bin, infinity);
    return juce::jmap(db, infinity, 0.0f, bounds.getBottom(), bounds.getY() + topPadding);
}
}  // namespace mc