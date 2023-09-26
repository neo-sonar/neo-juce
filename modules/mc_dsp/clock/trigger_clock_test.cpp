#include <mc_dsp/mc_dsp.hpp>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_template_test_macros.hpp>

TEST_CASE("dsp/clock: TriggerClock", "[dsp]")
{
    auto clock = mc::TriggerClock {};
    clock.setSampleRate(44'100.0);
    clock.setTickLength(mc::Seconds<double> { 1.0 });
    REQUIRE(clock.advance(32));
    REQUIRE_FALSE(clock.advance(32));
    REQUIRE(clock.advance(44'100));
    REQUIRE_FALSE(clock.advance(32));

    clock.reset();
    REQUIRE(clock.advance(32));
    REQUIRE_FALSE(clock.advance(32));
    REQUIRE(clock.advance(44'100));
    REQUIRE_FALSE(clock.advance(32));
}
