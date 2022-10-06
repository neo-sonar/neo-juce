namespace mc {

template <typename T>
auto channel(juce::dsp::AudioBlock<T> const& block, size_t index) -> Span<T>
{
    jassert(block.getNumChannels() > index);
    return { block.getChannelPointer(index), static_cast<size_t>(block.getNumSamples()) };
}

template <typename T>
auto addStereoFrame(juce::dsp::AudioBlock<T> const& block, size_t index, StereoFrame<T> frame) -> void
{
    block.addSample(0, static_cast<int>(index), frame.left);
    block.addSample(1, static_cast<int>(index), frame.right);
}

template <typename T>
auto rmsLevel(juce::dsp::AudioBlock<T> const& block) -> T
{
    auto sum = T { 0 };
    for (auto i { 0UL }; i < block.getNumChannels(); ++i) {
        auto const ch = channel(block, i);
        sum += ranges::accumulate(ch, T { 0 });
    }

    return sqrt(sum / static_cast<T>(block.getNumSamples() * block.getNumChannels()));
}

} // namespace mc
