#include <mc_modulation/mc_modulation.hpp>

#include "catch2/catch_approx.hpp"
#include "catch2/catch_test_macros.hpp"

TEST_CASE("modulation/core: ModulatorList", "[modulation][core]")
{
    auto state = juce::ValueTree {"MODULATOR_LIST"};
    auto list  = mc::modulation::ModulatorList {state, nullptr};
    CHECK(list.isEmpty());

    auto macro = juce::ValueTree {"MACRO"};
    state.addChild(macro, -1, nullptr);
    CHECK(list.size() == 1);

    auto* modulator = list.getModulatorFor(macro);
    CHECK(modulator != nullptr);
    CHECK(dynamic_cast<mc::modulation::ModulatorMacro*>(modulator) != nullptr);

    auto copy = mc::modulation::ModulatorList {state.createCopy(), nullptr};
    CHECK(copy.size() == 1);
    CHECK(list.getModulatorFor(macro) != nullptr);
    CHECK(dynamic_cast<mc::modulation::ModulatorMacro*>(list.getModulatorFor(macro)) != nullptr);
}
