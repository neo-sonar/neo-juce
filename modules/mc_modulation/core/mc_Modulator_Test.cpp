#include <mc_modulation/mc_modulation.hpp>

#include "catch2/catch_approx.hpp"
#include "catch2/catch_test_macros.hpp"

namespace
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
}  // namespace

TEST_CASE("modulation/core: Modulator", "[modulation][core]")
{
    // defaults
    auto modulator = TestModulator {};
    CHECK(modulator.state.hasType("test"));
    CHECK(modulator.getName() == juce::String {""});

    // default impl should not change the buffer
    auto buffer = juce::AudioBuffer<float> {1, 32};
    buffer.clear();

    modulator.prepare(44'100.0, 32);
    modulator.process(buffer);
    auto* const output = buffer.getWritePointer(0);
    for (auto i = 0; i < buffer.getNumSamples(); ++i) { CHECK(output[i] == 0.0f); }
    modulator.reset();
}
