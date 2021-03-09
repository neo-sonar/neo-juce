namespace
{

template<typename FloatT>
auto fillInternal(juce::AudioBuffer<FloatT>& buffer, FloatT value) noexcept -> void
{
    for (auto ch = 0; ch < buffer.getNumChannels(); ++ch)
    {
        auto* const samples = buffer.getWritePointer(ch);
        for (int i = 0; i < buffer.getNumSamples(); ++i) { samples[i] = value; }
    }
}

template<typename FloatT>
[[nodiscard]] auto containsNANsInternal(juce::AudioBuffer<FloatT> const& buffer) noexcept -> bool
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

template<typename FloatT>
[[nodiscard]] auto containsINFsInternal(juce::AudioBuffer<FloatT> const& buffer) noexcept -> bool
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

template<typename FloatT>
[[nodiscard]] auto equalInternal(juce::AudioBuffer<FloatT> const& lhs, juce::AudioBuffer<FloatT> const& rhs) noexcept
    -> bool
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

auto AudioBufferUtils::fill(juce::AudioBuffer<float>& buffer, float value) noexcept -> void
{
    ::fillInternal(buffer, value);
}
auto AudioBufferUtils::fill(juce::AudioBuffer<double>& buffer, double value) noexcept -> void
{
    ::fillInternal(buffer, value);
}

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