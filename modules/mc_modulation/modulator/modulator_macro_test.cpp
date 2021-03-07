#include <mc_modulation/mc_modulation.hpp>

#include "catch2/catch_test_macros.hpp"

TEST_CASE("modulation/modulator: ModulatorMacro::getName", "[modulation][modulator]")
{
    auto macro = mc::ModulatorMacro {juce::ValueTree {"macro"}};
    CHECK(macro.getName() == juce::String {"Macro"});
}