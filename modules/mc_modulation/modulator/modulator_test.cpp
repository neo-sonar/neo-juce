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
        ~TestPlayHead() override = default;
        auto getCurrentPosition(juce::AudioPlayHead::CurrentPositionInfo& /*result*/) -> bool override { return false; }
        auto canControlTransport() -> bool override { return false; }
    };

    // defaults
    auto modulator = TestModulator {};
    CHECK(modulator.getValueTree().hasType("test"));
    CHECK(modulator.getName() == juce::String {""});
    CHECK(modulator.getUndoManager() == nullptr);
    CHECK(modulator.getPlayHead() == nullptr);

    // default impl should not change the buffer
    auto midiBuffer = juce::MidiBuffer {};
    auto buffer     = juce::AudioBuffer<float> {1, 32};
    buffer.clear();

    modulator.prepareToPlay(44'100.0, 32);
    modulator.processBlock(buffer, midiBuffer);
    auto* const output = buffer.getWritePointer(0);
    for (auto i = 0; i < buffer.getNumSamples(); ++i) { CHECK(output[i] == 0.0f); }
    modulator.releaseResources();

    // play head
    auto playHead = TestPlayHead {};
    modulator.setPlayHead(&playHead);
    CHECK(modulator.getPlayHead() == &playHead);
}
