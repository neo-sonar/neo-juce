namespace mc {
SpectrumSource::SpectrumSource()
    : Thread("SpectrumSource")
    , _fft { 11 }
    , _windowing { static_cast<std::size_t>(_fft.getSize()), juce::dsp::WindowingFunction<float>::kaiser }
{
}

auto SpectrumSource::addAudioData(juce::AudioBuffer<float> const& buffer, int startChannel, int numChannels) -> void
{
    if (_abstractFifo.getFreeSpace() < buffer.getNumSamples()) { return; }

    int start1 {};
    int block1 {};
    int start2 {};
    int block2 {};
    _abstractFifo.prepareToWrite(buffer.getNumSamples(), start1, block1, start2, block2);
    _audioFifo.copyFrom(0, start1, buffer.getReadPointer(startChannel), block1);
    if (block2 > 0) { _audioFifo.copyFrom(0, start2, buffer.getReadPointer(startChannel, block1), block2); }

    for (int channel = startChannel; channel < startChannel + numChannels; ++channel) {
        if (block1 > 0) { _audioFifo.addFrom(0, start1, buffer.getReadPointer(channel), block1); }
        if (block2 > 0) { _audioFifo.addFrom(0, start2, buffer.getReadPointer(channel, block1), block2); }
    }
    _abstractFifo.finishedWrite(block1 + block2);
    _waitForData.signal();
}

auto SpectrumSource::setupAnalyser(int const audioFifoSize, double const sampleRateToUse) -> void
{
    _sampleRate = static_cast<float>(sampleRateToUse);
    _audioFifo.setSize(1, audioFifoSize);
    _abstractFifo.setTotalSize(audioFifoSize);
    _fftBuffer.setSize(1, _fft.getSize() * 2);
    _averager.setSize(3, _fft.getSize() / 2, false, true);

    startThread(5);
}

auto SpectrumSource::createPath(juce::Path& p, juce::Rectangle<float> const& bounds, float const minFreq) -> void
{
    p.clear();

    juce::ScopedLock const lockedForReading(_pathCreationLock);
    auto const* fftData = _averager.getReadPointer(0);
    auto const factor   = bounds.getWidth() / 10.0F;

    p.startNewSubPath(bounds.getX() + factor * indexToX(0, minFreq), binToY(fftData[0], bounds));
    p.preallocateSpace(_averager.getNumSamples());
    auto lastX = -100.0;
    for (int i = 0; i < _averager.getNumSamples(); ++i) {
        auto const x = bounds.getX() + factor * indexToX(static_cast<float>(i), minFreq);
        auto const y = binToY(fftData[i], bounds);
        if (lastX + 6 < x) {
            p.lineTo(static_cast<float>(x), static_cast<float>(y));
            lastX = x;
        }
    }
}

auto SpectrumSource::checkForNewData() -> bool
{
    auto const available = _newDataAvailable.load();
    _newDataAvailable.store(false);
    return available;
}

auto SpectrumSource::run() -> void
{
    while (!threadShouldExit()) {
        if (_abstractFifo.getNumReady() >= _fft.getSize()) {
            _fftBuffer.clear();

            auto start1 = 0;
            auto block1 = 0;
            auto start2 = 0;
            auto block2 = 0;

            _abstractFifo.prepareToRead(_fft.getSize(), start1, block1, start2, block2);
            if (block1 > 0) { _fftBuffer.copyFrom(0, 0, _audioFifo.getReadPointer(0, start1), block1); }
            if (block2 > 0) { _fftBuffer.copyFrom(0, block1, _audioFifo.getReadPointer(0, start2), block2); }
            _abstractFifo.finishedRead(block1 + block2);

            _windowing.multiplyWithWindowingTable(_fftBuffer.getWritePointer(0), size_t(_fft.getSize()));
            _fft.performFrequencyOnlyForwardTransform(_fftBuffer.getWritePointer(0));

            juce::ScopedLock const lockedForWriting(_pathCreationLock);
            _averager.addFrom(0, 0, _averager.getReadPointer(_averagerPtr), _averager.getNumSamples(), -1.0F);
            _averager.copyFrom(_averagerPtr,
                0,
                _fftBuffer.getReadPointer(0),
                _averager.getNumSamples(),
                1.0F / static_cast<float>(_averager.getNumSamples() * (_averager.getNumChannels() - 1)));
            _averager.addFrom(0, 0, _averager.getReadPointer(_averagerPtr), _averager.getNumSamples());
            if (++_averagerPtr == _averager.getNumChannels()) { _averagerPtr = 1; }

            _newDataAvailable.store(true);
        }

        if (_abstractFifo.getNumReady() < _fft.getSize()) { _waitForData.wait(20); }
    }
}

auto SpectrumSource::indexToX(float const index, float const minFreq) const -> float
{
    auto const freq = (_sampleRate * index) / static_cast<float>(_fft.getSize());
    return (freq > 0.01F) ? std::log(freq / minFreq) / std::log(2.0F) : 0.0F;
}

auto SpectrumSource::binToY(float const bin, juce::Rectangle<float> const& bounds) -> float
{
    auto const infinity   = -60.0F;
    auto const topPadding = bounds.getHeight() * 0.05F;
    auto const db         = juce::Decibels::gainToDecibels(bin, infinity);
    return juce::jmap(db, infinity, 0.0F, bounds.getBottom(), bounds.getY() + topPadding);
}
} // namespace mc
