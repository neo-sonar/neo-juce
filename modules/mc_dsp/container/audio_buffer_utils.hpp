#ifndef MODERN_CIRCUITS_JUCE_MODULES_AUDIO_BUFFER_UTILS_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_AUDIO_BUFFER_UTILS_HPP

#include <random>

namespace mc
{
struct AudioBufferUtils
{
    template<typename FloatT>
    [[nodiscard]] static auto createNoiseBuffer(int channels, int size, FloatT gain = 1.0) -> juce::AudioBuffer<FloatT>;

    [[nodiscard]] static auto containsNANs(juce::AudioBuffer<float> const& buffer) noexcept -> bool;
    [[nodiscard]] static auto containsNANs(juce::AudioBuffer<double> const& buffer) noexcept -> bool;

    [[nodiscard]] static auto containsINFs(juce::AudioBuffer<float> const& buffer) noexcept -> bool;
    [[nodiscard]] static auto containsINFs(juce::AudioBuffer<double> const& buffer) noexcept -> bool;

    [[nodiscard]] static auto equal(juce::AudioBuffer<float> const& lhs, juce::AudioBuffer<float> const& rhs) -> bool;
    [[nodiscard]] static auto equal(juce::AudioBuffer<double> const& lhs, juce::AudioBuffer<double> const& rhs) -> bool;
};

template<typename FloatT>
auto AudioBufferUtils::createNoiseBuffer(int const channels, int const size, FloatT const gain)
    -> juce::AudioBuffer<FloatT>
{
    std::random_device rd;
    std::mt19937 e2(rd());
    std::uniform_real_distribution<FloatT> dist(-1.0, 1.0);

    // fill with noise
    auto buffer = juce::AudioBuffer<FloatT> {channels, size};
    for (auto channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        for (int i = 0; i < buffer.getNumSamples(); ++i) { buffer.setSample(channel, i, dist(e2)); }
    }

    buffer.applyGain(gain);
    return buffer;
}
}  // namespace mc

#endif  // MODERN_CIRCUITS_JUCE_MODULES_AUDIO_BUFFER_UTILS_HPP
