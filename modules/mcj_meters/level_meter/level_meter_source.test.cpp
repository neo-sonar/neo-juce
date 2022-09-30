#include <mcj_meters/mcj_meters.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("meters/level_meter: LevelMeterSource", "[meters]")
{
    SECTION("uninitialized")
    {
        auto source = mc::LevelMeterSource {};
        REQUIRE(source.numChannels() == 0);
        REQUIRE(source.reductionLevel(0) == -1.0F);
    }

    SECTION("initialized")
    {
        auto source = mc::LevelMeterSource {};
        source.prepare({ 44'100.0, 512, 1 });
        REQUIRE(source.numChannels() == 1);
        REQUIRE(source.reductionLevel(0) == 1.0F);
        REQUIRE(source.maxLevel(0) == 0.0F);
        REQUIRE(source.rmsLevel(0) == 0.0F);
        REQUIRE_FALSE(source.clipFlag(0));

        // push silence
        auto buffer = juce::AudioBuffer<float> { 1, 512 };
        buffer.clear();
        source.measureBlock(buffer);
        REQUIRE(source.reductionLevel(0) == 1.0F);
        REQUIRE(source.maxLevel(0) == 0.0F);
        REQUIRE(source.rmsLevel(0) == 0.0F);
        REQUIRE_FALSE(source.clipFlag(0));
    }
}
