#include <mc_modulation/mc_modulation.hpp>

#include "catch2/catch_approx.hpp"
#include "catch2/catch_test_macros.hpp"

TEST_CASE("modulation/modulator: ModulatorMacro", "[modulation][modulator]")
{
    auto macro = mc::ModulatorMacro {juce::ValueTree {mc::ModulatorMacroIDs::type}};
    CHECK(macro.getValueTree().hasType(mc::ModulatorMacroIDs::type));
    CHECK(macro.getName() == juce::String {"Macro"});
    CHECK(macro.getGain() == Catch::Approx(1.0f));

    macro.setGain(2.0f);
    CHECK(macro.getGain() == Catch::Approx(2.0f));

    auto buffer = juce::AudioBuffer<float> {1, 32};
    buffer.clear();

    macro.prepare(44'100.0, 32);
    macro.process(buffer);

    auto* const output = buffer.getWritePointer(0);
    for (auto i = 0; i < buffer.getNumSamples(); ++i) { CHECK(output[i] == Catch::Approx(2.0f)); }

    macro.setGain(1.0f);
    buffer.clear();
    macro.process(buffer);
    for (auto i = 0; i < buffer.getNumSamples(); ++i) { CHECK(output[i] == Catch::Approx(1.0f)); }

    macro.reset();
}
