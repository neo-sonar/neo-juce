#include <mc_modulation/mc_modulation.hpp>

#include "catch2/catch_approx.hpp"
#include "catch2/catch_test_macros.hpp"

TEST_CASE("modulation/core: Modulator", "[modulation][core]")
{
    struct TestModulator : mc::modulation::Modulator
    {
        TestModulator() : mc::modulation::Modulator {juce::ValueTree {"test"}, nullptr} { }
        ~TestModulator() override = default;

        TestModulator(const TestModulator& other) = delete;
        TestModulator(TestModulator&& other)      = delete;
        auto operator=(const TestModulator& rhs) -> TestModulator& = delete;
        auto operator=(TestModulator&& rhs) -> TestModulator& = delete;
    };

    struct TestPlayHead : juce::AudioPlayHead
    {
        TestPlayHead()           = default;
        ~TestPlayHead() override = default;

        TestPlayHead(const TestPlayHead& other) = delete;
        TestPlayHead(TestPlayHead&& other)      = delete;
        auto operator=(const TestPlayHead& rhs) -> TestPlayHead& = delete;
        auto operator=(TestPlayHead&& rhs) -> TestPlayHead& = delete;

        auto getCurrentPosition(juce::AudioPlayHead::CurrentPositionInfo& /*result*/) -> bool override { return false; }
        auto canControlTransport() -> bool override { return false; }
    };

    // defaults
    auto modulator = TestModulator {};
    CHECK(modulator.state.hasType("test"));
    CHECK(modulator.getName() == juce::String {""});
    CHECK(modulator.getUndoManager() == nullptr);
    CHECK(modulator.getPlayHead() == nullptr);

    // default impl should not change the buffer
    auto buffer = juce::AudioBuffer<float> {1, 32};
    buffer.clear();

    modulator.prepare(44'100.0, 32);
    modulator.process(buffer);
    auto* const output = buffer.getWritePointer(0);
    for (auto i = 0; i < buffer.getNumSamples(); ++i) { CHECK(output[i] == 0.0f); }
    modulator.reset();

    // play head
    auto playHead = TestPlayHead {};
    modulator.setPlayHead(&playHead);
    CHECK(modulator.getPlayHead() == &playHead);
}
