#include <mc_dsp/mc_dsp.hpp>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_template_test_macros.hpp>

namespace {
template <typename FloatType>
auto createNoiseBuffer(int channels, int size) -> juce::AudioBuffer<FloatType>
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
} // namespace

// NOLINTNEXTLINE
#define REQUIRE_FOR_NANS(buffer)                                                                                       \
    for (auto channel = 0; channel < (buffer).getNumChannels(); ++channel) {                                           \
        auto* samples = (buffer).getWritePointer(channel);                                                             \
        for (int i = 0; i < (buffer).getNumSamples(); ++i) { REQUIRE_FALSE(std::isnan(samples[i])); }                  \
    }                                                                                                                  \
    do {                                                                                                               \
    } while (false)

// NOLINTNEXTLINE
#define REQUIRE_FOR_INFS(buffer)                                                                                       \
    for (auto channel = 0; channel < (buffer).getNumChannels(); ++channel) {                                           \
        auto* samples = (buffer).getWritePointer(channel);                                                             \
        for (int i = 0; i < (buffer).getNumSamples(); ++i) { REQUIRE_FALSE(std::isinf(samples[i])); }                  \
    }                                                                                                                  \
    do {                                                                                                               \
    } while (false)

TEMPLATE_TEST_CASE("dsp/fx: StereoWidth", "[dsp]", float, double) // NOLINT
{
    SECTION("width: 1.0 (no change)")
    {
        // test subject
        juce::dsp::ProcessorChain<mc::fx::StereoWidth> dspChain;
        dspChain.get<0>().prepare({ 44'100.0, uint32_t(512), uint32_t(2) });
        dspChain.get<0>().setParameters({ 1.0F });
        dspChain.get<0>().reset();

        // audio data
        auto buffer = createNoiseBuffer<TestType>(2, 512);

        // process chain
        auto originalBuffer = buffer;
        auto ioBuffer       = juce::dsp::AudioBlock<TestType>(buffer);
        auto const context  = juce::dsp::ProcessContextReplacing<TestType>(ioBuffer);
        dspChain.process(context);

        // check
        REQUIRE_FOR_NANS(buffer);
        REQUIRE_FOR_INFS(buffer);
        for (auto channel = 0; channel < buffer.getNumChannels(); ++channel) {
            auto* originalData  = originalBuffer.getWritePointer(channel);
            auto* processedData = buffer.getWritePointer(channel);

            // check that original & processed buffer contain the same data
            for (int i = 0; i < buffer.getNumSamples(); ++i) {
                REQUIRE(processedData[i] == Catch::Approx(originalData[i]));
            }
        }
    }

    SECTION("width: 0.0 (mono)")
    {
        // test subject
        juce::dsp::ProcessorChain<mc::fx::StereoWidth> dspChain;
        dspChain.get<0>().prepare({ 96'000.0, uint32_t(512), uint32_t(2) });
        dspChain.get<0>().setParameters({ 0.0F });
        dspChain.get<0>().reset();

        // audio data
        auto buffer = createNoiseBuffer<TestType>(2, 512);

        // process chain
        auto ioBuffer      = juce::dsp::AudioBlock<TestType>(buffer);
        auto const context = juce::dsp::ProcessContextReplacing<TestType>(ioBuffer);
        dspChain.process(context);

        // check
        REQUIRE_FOR_NANS(buffer);
        REQUIRE_FOR_INFS(buffer);
        auto* left  = buffer.getWritePointer(0);
        auto* right = buffer.getWritePointer(1);

        for (int i = 0; i < buffer.getNumSamples(); ++i) {
            // check that left & right buffers contain the same data.
            REQUIRE(left[i] == Catch::Approx(right[i]));
        }
    }
}

TEMPLATE_TEST_CASE("dsp/fx: AirWindowsDeRez", "[dsp]", float, double) // NOLINT
{
    using T = TestType;

    auto proc   = mc::fx::AirWindowsDeRez<T> {};
    auto buffer = juce::AudioBuffer<T> { 2, 512 };
    auto block  = juce::dsp::AudioBlock<T> { buffer };
    auto ctx    = juce::dsp::ProcessContextReplacing { block };

    proc.parameter({ T(1), T(1) });
    proc.prepare({ 44'100.0, 512, 2 });
    proc.process(ctx);
    proc.reset();
}
