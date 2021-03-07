#include <mc_modulation/mc_modulation.hpp>

#include "catch2/catch_approx.hpp"
#include "catch2/catch_test_macros.hpp"

TEST_CASE("modulation/modulator: Modulator", "[modulation][modulator]")
{
    struct TestModulator : mc::Modulator
    {
        TestModulator() : mc::Modulator {juce::ValueTree {"test"}, nullptr} { }
        ~TestModulator() override = default;
    };

    struct TestPlayHead : juce::AudioPlayHead
    {
        TestPlayHead() : juce::AudioPlayHead {} { }
        auto getCurrentPosition(juce::AudioPlayHead::CurrentPositionInfo&) -> bool override { return false; }
        auto canControlTransport() -> bool override { return false; }
    };

    auto modulator = TestModulator {};
    CHECK(modulator.getValueTree().hasType("test"));
    CHECK(modulator.getName() == juce::String {""});
    CHECK(modulator.getUndoManager() == nullptr);
    CHECK(modulator.getPlayHead() == nullptr);

    auto playHead = TestPlayHead {};
    modulator.setPlayHead(&playHead);
    CHECK(modulator.getPlayHead() == &playHead);
}
