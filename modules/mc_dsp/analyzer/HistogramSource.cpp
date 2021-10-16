namespace mc {

auto HistogramSource::prepare(double sampleRate, std::uint32_t blockSize) -> void
{
    sampleRate_ = sampleRate;
    summingBuffer_.setSize(1, static_cast<int>(blockSize));
    reset();
}

auto HistogramSource::process(juce::AudioBuffer<float> const& buffer) -> void
{
    summingBuffer_.clear();
    AudioBufferUtils::sumToMono(buffer, summingBuffer_);
    // auto minmax = summingBuffer_.findMinMax(0, 0, buffer.getNumSamples());
    // processSample(minmax.getEnd(), buffer.getNumSamples());
    processSample(buffer.getSample(0, 0), static_cast<std::uint32_t>(buffer.getNumSamples()));
}

auto HistogramSource::processSample(float sample, std::uint32_t /*unused*/) -> void
{
    // timeSinceLastSample_ += samplesToMicroseconds(sampleCountToAdvance, sampleRate_);
    // if (timeSinceLastSample_ >= refreshRate_) {
    //     queue_.try_enqueue(sample);
    //     timeSinceLastSample_ = Microseconds<double> { 0.0 };
    // }

    lastValue_ = sample;
}

auto HistogramSource::reset() -> void { timeSinceLastSample_ = Microseconds<double> { 0.0 }; }

auto HistogramSource::popSample() -> float
{
    // auto samples = SmallVector<float, 4> {};
    // queue_.try_dequeue_bulk(std::back_inserter(samples), samples.capacity());
    // if (!samples.empty()) {
    //     auto const sum     = std::accumulate(std::begin(samples), std::end(samples), 0.0f);
    //     auto const average = sum / std::max<std::size_t>(samples.size(), 1U);
    //     lastValue_         = average;
    // }
    return lastValue_;
}

} // namespace mc