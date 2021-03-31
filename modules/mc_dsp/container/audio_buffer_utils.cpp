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
auto sumToMonoInternal(juce::AudioBuffer<FloatT> const& src, juce::AudioBuffer<FloatT>& dst) noexcept -> void
{
    jassert(dst.getNumChannels() == 1);
    jassert(src.getNumChannels() >= 1);
    jassert(src.getNumSamples() == dst.getNumSamples());

    dst.clear();
    auto const numSrcChannels = src.getNumChannels();
    for (int channel = 0; channel < numSrcChannels; channel++)
    {
        dst.addFrom(0, 0, src, channel, 0, src.getNumSamples());
    }

    dst.applyGain(FloatT {1} / static_cast<FloatT>(numSrcChannels));
}

template<typename FloatT>
auto splitInternal(juce::AudioBuffer<FloatT> const& src, juce::AudioBuffer<FloatT>& dst) noexcept -> void
{
    jassert(dst.getNumChannels() >= 1);
    jassert(src.getNumChannels() == 1);
    jassert(src.getNumSamples() == dst.getNumSamples());

    dst.clear();
    for (int channel = 0; channel < dst.getNumChannels(); channel++)
    {
        dst.copyFrom(channel, 0, src, 0, 0, src.getNumSamples());
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
[[nodiscard]] auto allOfInternal(juce::AudioBuffer<FloatT> const& buffer, FloatT const value) noexcept -> bool
{
    auto const numChannels = buffer.getNumChannels();
    auto const numSamples  = buffer.getNumSamples();
    for (auto ch = 0; ch < numChannels; ++ch)
    {
        for (auto i = 0; i < numSamples; ++i)
        {
            if (buffer.getSample(ch, i) != value) { return false; }
        }
    }
    return true;
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

auto AudioBufferUtils::sumToMono(juce::AudioBuffer<float> const& src, juce::AudioBuffer<float>& dst) noexcept -> void
{
    ::sumToMonoInternal(src, dst);
}
auto AudioBufferUtils::sumToMono(juce::AudioBuffer<double> const& src, juce::AudioBuffer<double>& dst) noexcept -> void
{
    ::sumToMonoInternal(src, dst);
}

auto AudioBufferUtils::split(juce::AudioBuffer<float> const& src, juce::AudioBuffer<float>& dst) noexcept -> void
{
    ::splitInternal(src, dst);
}
auto AudioBufferUtils::split(juce::AudioBuffer<double> const& src, juce::AudioBuffer<double>& dst) noexcept -> void
{
    ::splitInternal(src, dst);
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

auto AudioBufferUtils::allOf(juce::AudioBuffer<float> const& buffer, float value) noexcept -> bool
{
    return ::allOfInternal(buffer, value);
}

auto AudioBufferUtils::allOf(juce::AudioBuffer<double> const& buffer, double value) noexcept -> bool
{
    return ::allOfInternal(buffer, value);
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