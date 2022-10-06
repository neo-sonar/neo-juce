#include <mc_dsp/mc_dsp.hpp>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("dsp/units: barsToSamples", "[dsp]")
{
    REQUIRE(mc::barsToSamples(1.0, 240.0, 44'100.0) == Catch::Approx(44'100.0));
    REQUIRE(mc::barsToSamples(1.0, 120.0, 44'100.0) == Catch::Approx(88'200.0));
    REQUIRE(mc::barsToSamples(1.0, 120.0, 88'200.0) == Catch::Approx(176'400.0));

    REQUIRE(mc::barsToSamples(2.0, 120.0, 44'100.0) == Catch::Approx(176'400.0));
    REQUIRE(mc::barsToSamples(1.0 / 16.0, 240.0, 44'100.0) == Catch::Approx(2756.25));
    REQUIRE(mc::barsToSamples(1.0 / 8.0, 240.0, 44'100.0) == Catch::Approx(5512.5));
}

TEST_CASE("dsp/units: barsToSeconds", "[dsp]")
{
    REQUIRE(mc::barsToSeconds(120.0, 2.0, 1.0) == mc::Seconds<double> { 4.0 });
    REQUIRE(mc::barsToSeconds(120.0, 1.0, 1.0) == mc::Seconds<double> { 2.0 });
    REQUIRE(mc::barsToSeconds(120.0, 1.0, 4.0) == mc::Seconds<double> { 0.5 });
}
