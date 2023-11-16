#include <neo_meters/neo_meters.hpp>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_template_test_macros.hpp>

TEST_CASE("meters/waveform: WaveformSource", "[meters]")
{
    auto source = neo::WaveformSource {};
    REQUIRE(source.numChannels() == 0);

    source.prepare({ 44'100.0, 512, 2 });
    REQUIRE(source.numChannels() == 2);

    auto left = juce::Path {};
    source.makeChannelPath(left, 0);
    REQUIRE_FALSE(left.isEmpty());

    auto right = juce::Path {};
    source.makeChannelPath(right, 1);
    REQUIRE_FALSE(right.isEmpty());
}
