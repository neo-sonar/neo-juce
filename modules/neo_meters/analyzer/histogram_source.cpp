namespace neo {

auto HistogramSource::prepare(double sampleRate, std::uint32_t blockSize) -> void
{
    _sampleRate = sampleRate;
    _summingBuffer.setSize(1, static_cast<int>(blockSize));
    reset();
}

auto HistogramSource::process(juce::AudioBuffer<float> const& buffer) -> void
{
    _summingBuffer.clear();
    AudioBufferUtils::sumToMono(buffer, _summingBuffer);
    processSample(buffer.getSample(0, 0), static_cast<std::uint32_t>(buffer.getNumSamples()));
}

auto HistogramSource::processSample(float sample, std::uint32_t /*unused*/) -> void { _lastValue = sample; }

auto HistogramSource::reset() -> void { _timeSinceLastSample = Microseconds<double> { 0.0 }; }

auto HistogramSource::popSample() -> float { return _lastValue; }

} // namespace neo
