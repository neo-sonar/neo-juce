namespace neo {

template <typename T>
auto channel(juce::dsp::AudioBlock<T> const& block, size_t index) -> std::span<T>
{
    jassert(block.getNumChannels() > index);
    return { block.getChannelPointer(index), static_cast<size_t>(block.getNumSamples()) };
}

template <typename T>
auto rmsLevel(juce::dsp::AudioBlock<T> const& block) -> T
{
    auto sum = T { 0 };
    for (auto i { 0UL }; i < block.getNumChannels(); ++i) {
        auto const ch = channel(block, i);
        sum += std::accumulate(ch.begin(), ch.end(), T { 0 });
    }

    return std::sqrt(sum / static_cast<T>(block.getNumSamples() * block.getNumChannels()));
}

} // namespace neo
