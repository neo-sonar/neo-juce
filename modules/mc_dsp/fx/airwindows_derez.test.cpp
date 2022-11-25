#include <mc_dsp/mc_dsp.hpp>

#include <catch2/catch_template_test_macros.hpp>

TEMPLATE_TEST_CASE("dsp/fx: AirWindowsDeRez", "[dsp]", float, double) // NOLINT
{
    using T = TestType;

    auto proc   = mc::fx::AirWindowsDeRez<T> {};
    auto buffer = juce::AudioBuffer<T> { 2, 512 };
    auto block  = juce::dsp::AudioBlock<T> { buffer };
    auto ctx    = juce::dsp::ProcessContextReplacing { block };

    proc.parameter({ T(1), T(1) });
    proc.prepare({ 44'100.0, 512, 2 });
    proc.process(ctx);
    proc.reset();
}
