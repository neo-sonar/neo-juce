#include <mc_dsp/mc_dsp.hpp>

#include "catch2/catch_template_test_macros.hpp"

TEMPLATE_TEST_CASE("dsp/container: AudioBufferUtils::containsNANs", "[dsp][container]", float, double)
{
    auto buffer = juce::AudioBuffer<TestType> {2, 512};
    CHECK_FALSE(mc::AudioBufferUtils::containsNANs(buffer));
}

TEMPLATE_TEST_CASE("dsp/container: AudioBufferUtils::containsINFs", "[dsp][container]", float, double)
{
    auto buffer = juce::AudioBuffer<TestType> {2, 512};
    CHECK_FALSE(mc::AudioBufferUtils::containsINFs(buffer));
}

TEMPLATE_TEST_CASE("dsp/container: AudioBufferUtils::equal", "[dsp][container]", float, double)
{
    SECTION("same buffer")
    {
        auto buffer = juce::AudioBuffer<TestType> {2, 512};
        CHECK(mc::AudioBufferUtils::equal(buffer, buffer));
    }
}