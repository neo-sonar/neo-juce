#include <mc_dsp/mc_dsp.hpp>

#include <catch2/catch.hpp>

#include "mc/random.hpp"

template <typename FloatType>
inline auto createNoiseBuffer(int channels, int size) -> juce::AudioBuffer<FloatType>
{
    std::random_device rd;
    std::mt19937 e2(rd());
    std::uniform_real_distribution<FloatType> dist(-1.0, 1.0);

    // fill with noise
    auto buffer = juce::AudioBuffer<FloatType> { channels, size };
    for (auto channel = 0; channel < buffer.getNumChannels(); ++channel) {
        for (int i = 0; i < buffer.getNumSamples(); ++i) { buffer.setSample(channel, i, dist(e2)); }
    }

    return buffer;
}

#define CHECK_FOR_NANS(buffer)                                                                                         \
    for (auto channel = 0; channel < (buffer).getNumChannels(); ++channel) {                                           \
        auto* samples = (buffer).getWritePointer(channel);                                                             \
        for (int i = 0; i < (buffer).getNumSamples(); ++i) { CHECK_FALSE(std::isnan(samples[i])); }                    \
    }                                                                                                                  \
    do {                                                                                                               \
    } while (false)

#define CHECK_FOR_INFS(buffer)                                                                                         \
    for (auto channel = 0; channel < (buffer).getNumChannels(); ++channel) {                                           \
        auto* samples = (buffer).getWritePointer(channel);                                                             \
        for (int i = 0; i < (buffer).getNumSamples(); ++i) { CHECK_FALSE(std::isinf(samples[i])); }                    \
    }                                                                                                                  \
    do {                                                                                                               \
    } while (false)

TEMPLATE_TEST_CASE("dsp/processor: StereoWidth", "[dsp][processor]", float, double)
{
    SECTION("width: 1.0 (no change)")
    {
        // test subject
        juce::dsp::ProcessorChain<mc::dsp::StereoWidth> dspChain;
        dspChain.get<0>().prepare({ 44'100.0, uint32_t(512), uint32_t(2) });
        dspChain.get<0>().setParameters({ 1.0f });
        dspChain.get<0>().reset();

        // audio data
        auto buffer = createNoiseBuffer<TestType>(2, 512);

        // process chain
        auto originalBuffer = buffer;
        auto ioBuffer       = juce::dsp::AudioBlock<TestType>(buffer);
        auto const context  = juce::dsp::ProcessContextReplacing<TestType>(ioBuffer);
        dspChain.process(context);

        // check
        CHECK_FOR_NANS(buffer);
        CHECK_FOR_INFS(buffer);
        for (auto channel = 0; channel < buffer.getNumChannels(); ++channel) {
            auto* originalData  = originalBuffer.getWritePointer(channel);
            auto* processedData = buffer.getWritePointer(channel);

            // check that original & processed buffer contain the same data
            for (int i = 0; i < buffer.getNumSamples(); ++i) { CHECK(processedData[i] == Approx(originalData[i])); }
        }
    }

    SECTION("width: 0.0 (mono)")
    {
        // test subject
        juce::dsp::ProcessorChain<mc::dsp::StereoWidth> dspChain;
        dspChain.get<0>().prepare({ 96'000.0, uint32_t(512), uint32_t(2) });
        dspChain.get<0>().setParameters({ 0.0f });
        dspChain.get<0>().reset();

        // audio data
        auto buffer = createNoiseBuffer<TestType>(2, 512);

        // process chain
        auto ioBuffer      = juce::dsp::AudioBlock<TestType>(buffer);
        auto const context = juce::dsp::ProcessContextReplacing<TestType>(ioBuffer);
        dspChain.process(context);

        // check
        CHECK_FOR_NANS(buffer);
        CHECK_FOR_INFS(buffer);
        auto* left  = buffer.getWritePointer(0);
        auto* right = buffer.getWritePointer(1);

        for (int i = 0; i < buffer.getNumSamples(); ++i) {
            // check that left & right buffers contain the same data.
            CHECK(left[i] == Approx(right[i]));
        }
    }
}
