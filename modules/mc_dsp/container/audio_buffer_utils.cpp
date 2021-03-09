namespace
{

template<typename SampleType>
[[nodiscard]] auto containsNANsInternal(juce::AudioBuffer<SampleType> const& buffer) noexcept -> bool
{
    for (auto channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        auto const* const samples = buffer.getReadPointer(channel);
        for (int i = 0; i < buffer.getNumSamples(); ++i)
        {
            if (std::isnan(samples[i])) { return true; }
        }
    }

    return false;
}

template<typename SampleType>
[[nodiscard]] auto containsINFsInternal(juce::AudioBuffer<SampleType> const& buffer) noexcept -> bool
{
    for (auto channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        auto const* const samples = buffer.getReadPointer(channel);
        for (int i = 0; i < buffer.getNumSamples(); ++i)
        {
            if (std::isinf(samples[i])) { return true; }
        }
    }

    return false;
}

template<typename SampleType>
[[nodiscard]] auto equalInternal(juce::AudioBuffer<SampleType> const& lhs,
                                 juce::AudioBuffer<SampleType> const& rhs) noexcept -> bool
{
    if (lhs.getNumChannels() != rhs.getNumChannels()) { return false; }
    if (lhs.getNumSamples() != rhs.getNumSamples()) { return false; }
    for (auto ch = 0; ch < lhs.getNumChannels(); ++ch)
    {
        auto* l = lhs.getReadPointer(ch);
        auto* r = rhs.getReadPointer(ch);
        for (int i = 0; i < lhs.getNumSamples(); ++i)
        {
            if (l[i] != r[i]) { return false; }
        }
    }
    return true;
}
}  // namespace

namespace mc
{
auto AudioBufferUtils::containsNANs(juce::AudioBuffer<float> const& buffer) noexcept -> bool
{
    return ::containsNANsInternal(buffer);
}
auto AudioBufferUtils::containsNANs(juce::AudioBuffer<double> const& buffer) noexcept -> bool
{
    return ::containsNANsInternal(buffer);
}

auto AudioBufferUtils::containsINFs(juce::AudioBuffer<float> const& buffer) noexcept -> bool
{
    return ::containsINFsInternal(buffer);
}
auto AudioBufferUtils::containsINFs(juce::AudioBuffer<double> const& buffer) noexcept -> bool
{
    return ::containsINFsInternal(buffer);
}

auto AudioBufferUtils::equal(juce::AudioBuffer<float> const& lhs, juce::AudioBuffer<float> const& rhs) -> bool
{
    return ::equalInternal(lhs, rhs);
}
auto AudioBufferUtils::equal(juce::AudioBuffer<double> const& lhs, juce::AudioBuffer<double> const& rhs) -> bool
{
    return ::equalInternal(lhs, rhs);
}

}  // namespace mc