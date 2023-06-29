#include <mc_synth/mc_synth.hpp>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

TEMPLATE_TEST_CASE("synth/wavetable: unisonDetuneForVoice", "[synth]", float, double) // NOLINT
{
    using namespace mc;
    using T = TestType;

    REQUIRE(unisonDetuneForVoice<T>(1, 0) == T { 0 });

    auto voices = GENERATE(2, 3, 4, 5, 6, 7, 8);
    REQUIRE(unisonDetuneForVoice<T>(voices, 0) == Catch::Approx(T { -1 }));
    REQUIRE(unisonDetuneForVoice<T>(voices, voices - 1) == Catch::Approx(T { 1 }));

    // auto osc = mc::UnisonWavetableOsc<float, 16> {};
    // juce::ignoreUnused(osc);
}
