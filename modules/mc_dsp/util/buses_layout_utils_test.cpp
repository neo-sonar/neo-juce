#include <mc_dsp/mc_dsp.hpp>

#include "catch2/catch_test_macros.hpp"

TEST_CASE("util: BusesLayoutUtils::isSameInOut", "[util]")
{
    SECTION("mono/stereo")
    {
        auto l1        = juce::AudioProcessor::BusesLayout {};
        l1.inputBuses  = juce::AudioChannelSet::mono();
        l1.outputBuses = juce::AudioChannelSet::stereo();
        CHECK_FALSE(mc::BusesLayoutUtils::isSameInOut(l1));

        auto l2        = juce::AudioProcessor::BusesLayout {};
        l2.inputBuses  = juce::AudioChannelSet::stereo();
        l2.outputBuses = juce::AudioChannelSet::mono();
        CHECK_FALSE(mc::BusesLayoutUtils::isSameInOut(l2));
    }

    SECTION("mono")
    {
        auto layout        = juce::AudioProcessor::BusesLayout {};
        layout.inputBuses  = juce::AudioChannelSet::mono();
        layout.outputBuses = juce::AudioChannelSet::mono();
        CHECK(mc::BusesLayoutUtils::isSameInOut(layout));
    }

    SECTION("stereo")
    {
        auto layout        = juce::AudioProcessor::BusesLayout {};
        layout.inputBuses  = juce::AudioChannelSet::stereo();
        layout.outputBuses = juce::AudioChannelSet::stereo();
        CHECK(mc::BusesLayoutUtils::isSameInOut(layout));
    }
}

TEST_CASE("util: BusesLayoutUtils::isStereoInOut", "[util]")
{
    SECTION("mono/stereo")
    {
        auto l1        = juce::AudioProcessor::BusesLayout {};
        l1.inputBuses  = juce::AudioChannelSet::mono();
        l1.outputBuses = juce::AudioChannelSet::stereo();
        CHECK_FALSE(mc::BusesLayoutUtils::isStereoInOut(l1));

        auto l2        = juce::AudioProcessor::BusesLayout {};
        l2.inputBuses  = juce::AudioChannelSet::stereo();
        l2.outputBuses = juce::AudioChannelSet::mono();
        CHECK_FALSE(mc::BusesLayoutUtils::isStereoInOut(l2));
    }

    SECTION("mono")
    {
        auto layout        = juce::AudioProcessor::BusesLayout {};
        layout.inputBuses  = juce::AudioChannelSet::mono();
        layout.outputBuses = juce::AudioChannelSet::mono();
        CHECK_FALSE(mc::BusesLayoutUtils::isStereoInOut(layout));
    }

    SECTION("stereo")
    {
        auto layout        = juce::AudioProcessor::BusesLayout {};
        layout.inputBuses  = juce::AudioChannelSet::stereo();
        layout.outputBuses = juce::AudioChannelSet::stereo();
        CHECK(mc::BusesLayoutUtils::isStereoInOut(layout));
    }
}
