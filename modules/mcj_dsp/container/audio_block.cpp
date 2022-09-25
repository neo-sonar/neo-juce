namespace mc {

template <typename T>
auto channel(juce::dsp::AudioBlock<T> const& block, size_t index) -> Span<T>
{
    jassert(block.getNumChannels() > index);
    return { block.getChannelPointer(index), static_cast<size_t>(block.getNumSamples()) };
}

template <typename T>
auto addStereoFrame(juce::dsp::AudioBlock<T> const& block, size_t index, dsp::StereoFrame<T> frame) -> void
{
    block.addSample(0, static_cast<int>(index), frame.left);
    block.addSample(1, static_cast<int>(index), frame.right);
}

} // namespace mc
