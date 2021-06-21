namespace mc
{

void OscilloscopeSource::process(juce::AudioBuffer<float> const& buffer)
{
    auto const numSamples = buffer.getNumSamples();
    auto const* data      = buffer.getReadPointer(0);
    processInternal(data, static_cast<std::size_t>(numSamples));
}

void OscilloscopeSource::process(juce::AudioBuffer<double> const& buffer)
{
    auto const numSamples = buffer.getNumSamples();
    auto const* data      = buffer.getReadPointer(0);
    processInternal(data, static_cast<std::size_t>(numSamples));
}

auto OscilloscopeSource::getQueue() -> AudioBufferQueue<double>& { return audioBufferQueue_; }

}  // namespace mc