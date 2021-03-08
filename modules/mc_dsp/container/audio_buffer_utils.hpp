#ifndef MODERN_CIRCUITS_JUCE_MODULES_AUDIO_BUFFER_UTILS_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_AUDIO_BUFFER_UTILS_HPP

#include <random>

namespace mc
{
struct AudioBufferUtils
{
    template<typename SampleType>
    [[nodiscard]] static auto createNoiseBuffer(int channels, int size) -> juce::AudioBuffer<SampleType>
    {
        std::random_device rd;
        std::mt19937 e2(rd());
        std::uniform_real_distribution<SampleType> dist(-1.0, 1.0);

        // fill with noise
        auto buffer = juce::AudioBuffer<SampleType> {channels, size};
        for (auto channel = 0; channel < buffer.getNumChannels(); ++channel)
        {
            for (int i = 0; i < buffer.getNumSamples(); ++i) { buffer.setSample(channel, i, dist(e2)); }
        }

        return buffer;
    }

    template<typename SampleType>
    [[nodiscard]] static auto containsNANs(juce::AudioBuffer<SampleType> const& buffer) noexcept -> bool
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
    [[nodiscard]] static auto containsINFs(juce::AudioBuffer<SampleType> const& buffer) noexcept -> bool
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
    [[nodiscard]] static auto equal(juce::AudioBuffer<SampleType> const& lhs,
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
};

}  // namespace mc

#endif  // MODERN_CIRCUITS_JUCE_MODULES_AUDIO_BUFFER_UTILS_HPP
