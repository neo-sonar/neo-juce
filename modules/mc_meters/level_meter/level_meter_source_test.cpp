#include <mc_meters/mc_meters.hpp>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("meters/level_meter: LevelMeterSource", "[meters]")
{
    SECTION("uninitialized")
    {
        auto source = mc::LevelMeterSource {};
        REQUIRE(source.numChannels() == 0);
        REQUIRE(source.reductionLevel(0) == Catch::Approx(-1.0));
    }

    SECTION("initialized")
    {
        auto source = mc::LevelMeterSource {};
        source.prepare({ 44'100.0, 512, 1 });
        REQUIRE(source.numChannels() == 1);
        REQUIRE(source.reductionLevel(0) == Catch::Approx(1.0));
        REQUIRE(source.maxLevel(0) == Catch::Approx(0.0));
        REQUIRE(source.rmsLevel(0) == Catch::Approx(0.0));
        REQUIRE_FALSE(source.clipFlag(0));

        // push silence
        auto buffer = juce::AudioBuffer<float> { 1, 512 };
        buffer.clear();
        source.measureBlock(buffer);
        REQUIRE(source.reductionLevel(0) == Catch::Approx(1.0));
        REQUIRE(source.maxLevel(0) == Catch::Approx(0.0));
        REQUIRE(source.rmsLevel(0) == Catch::Approx(0.0));
        REQUIRE_FALSE(source.clipFlag(0));
    }
}
