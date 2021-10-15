#include <mc_dsp/mc_dsp.hpp>

#include <catch2/catch.hpp>

TEMPLATE_TEST_CASE("dsp/container: AudioBufferUtils::sumToMono", "", float, double)
{
    auto src = juce::AudioBuffer<TestType> { 2, 512 };
    auto dst = juce::AudioBuffer<TestType> { 1, 512 };

    mc::AudioBufferUtils::fill(src, TestType { 0.5 });
    mc::AudioBufferUtils::sumToMono(src, dst);
    CHECK(mc::AudioBufferUtils::allOf(dst, TestType { 0.5 }));
}

TEMPLATE_TEST_CASE("dsp/container: AudioBufferUtils::split", "", float, double)
{
    auto src = juce::AudioBuffer<TestType> { 1, 512 };
    auto dst = juce::AudioBuffer<TestType> { 4, 512 };

    mc::AudioBufferUtils::fill(src, TestType { 2.0 });
    mc::AudioBufferUtils::split(src, dst);
    CHECK(mc::AudioBufferUtils::allOf(dst, TestType { 2.0 }));
}

TEMPLATE_TEST_CASE("dsp/container: AudioBufferUtils::containsNANs", "", float, double)
{
    auto buffer = juce::AudioBuffer<TestType> { 2, 512 };
    mc::AudioBufferUtils::fill(buffer, TestType { 0.5 });
    CHECK_FALSE(mc::AudioBufferUtils::containsNANs(buffer));
}

TEMPLATE_TEST_CASE("dsp/container: AudioBufferUtils::containsINFs", "", float, double)
{
    auto buffer = juce::AudioBuffer<TestType> { 2, 512 };
    mc::AudioBufferUtils::fill(buffer, TestType { 0.5 });
    CHECK_FALSE(mc::AudioBufferUtils::containsINFs(buffer));
}

TEMPLATE_TEST_CASE("dsp/container: AudioBufferUtils::equal", "", float, double)
{
    SECTION("same buffer")
    {
        auto buffer = juce::AudioBuffer<TestType> { 2, 512 };
        mc::AudioBufferUtils::fill(buffer, TestType { 0.5 });
        CHECK(mc::AudioBufferUtils::equal(buffer, buffer));
    }
}