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
    processSample(buffer.getSample(0, 0), static_cast<std::uint32_t>(buffer.getNumSamples()));
}

auto HistogramSource::processSample(float sample, std::uint32_t /*unused*/) -> void { lastValue_ = sample; }

auto HistogramSource::reset() -> void { timeSinceLastSample_ = Microseconds<double> { 0.0 }; }

auto HistogramSource::popSample() -> float { return lastValue_; }

} // namespace mc