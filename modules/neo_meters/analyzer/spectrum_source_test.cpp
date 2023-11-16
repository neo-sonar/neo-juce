#include <neo_meters/neo_meters.hpp>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_template_test_macros.hpp>

TEST_CASE("meters/analyzer: SpectrumSource", "[meters]")
{
    auto thread = juce::TimeSliceThread { "SpectrumThread" };
    auto source = neo::SpectrumSource { thread };
    REQUIRE(source.getSampleRate() == Catch::Approx(0.0));

    source.prepare({ 44'100.0, 512, 2 });
    REQUIRE(source.getSampleRate() == Catch::Approx(44'100.0));

    auto path = source.makePath({ 0.0F, 0.0F, 100.0F, 100.0F });
    REQUIRE_FALSE(path.isEmpty());
}
