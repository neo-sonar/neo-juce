#include <mc_dsp/mc_dsp.hpp>

#include <catch2/catch_template_test_macros.hpp>

TEMPLATE_TEST_CASE("dsp/container: AudioBufferUtils::sumToMono", "[dsp]", float, double)
{
    auto src = juce::AudioBuffer<TestType> { 2, 512 };
    auto dst = juce::AudioBuffer<TestType> { 1, 512 };

    mc::AudioBufferUtils::fill(src, TestType { 0.5 });
    mc::AudioBufferUtils::sumToMono(src, dst);
    REQUIRE(mc::AudioBufferUtils::allOf(dst, TestType { 0.5 }));
}

TEMPLATE_TEST_CASE("dsp/container: AudioBufferUtils::split", "[dsp]", float, double)
{
    auto src = juce::AudioBuffer<TestType> { 1, 512 };
    auto dst = juce::AudioBuffer<TestType> { 4, 512 };

    mc::AudioBufferUtils::fill(src, TestType { 2.0 });
    mc::AudioBufferUtils::split(src, dst);
    REQUIRE(mc::AudioBufferUtils::allOf(dst, TestType { 2.0 }));
}

TEMPLATE_TEST_CASE("dsp/container: AudioBufferUtils::containsNANs", "[dsp]", float, double)
{
    auto buffer = juce::AudioBuffer<TestType> { 2, 512 };
    mc::AudioBufferUtils::fill(buffer, TestType { 0.5 });
    REQUIRE_FALSE(mc::AudioBufferUtils::containsNANs(buffer));
}

TEMPLATE_TEST_CASE("dsp/container: AudioBufferUtils::containsINFs", "[dsp]", float, double)
{
    auto buffer = juce::AudioBuffer<TestType> { 2, 512 };
    mc::AudioBufferUtils::fill(buffer, TestType { 0.5 });
    REQUIRE_FALSE(mc::AudioBufferUtils::containsINFs(buffer));
}

TEMPLATE_TEST_CASE("dsp/container: AudioBufferUtils::equal", "[dsp]", float, double)
{
    SECTION("same buffer")
    {
        auto buffer = juce::AudioBuffer<TestType> { 2, 512 };
        mc::AudioBufferUtils::fill(buffer, TestType { 0.5 });
        REQUIRE(mc::AudioBufferUtils::equal(buffer, buffer));
    }
}
