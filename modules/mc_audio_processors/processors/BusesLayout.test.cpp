#include <mc_audio_processors/mc_audio_processors.hpp>

#include <catch2/catch_template_test_macros.hpp>

TEST_CASE("audio_processors/processors: isSameInOut", "[audio_processors]")
{
    SECTION("mono/stereo")
    {
        auto l1        = juce::AudioProcessor::BusesLayout {};
        l1.inputBuses  = juce::AudioChannelSet::mono();
        l1.outputBuses = juce::AudioChannelSet::stereo();
        REQUIRE_FALSE(mc::isSameInOut(l1));

        auto l2        = juce::AudioProcessor::BusesLayout {};
        l2.inputBuses  = juce::AudioChannelSet::stereo();
        l2.outputBuses = juce::AudioChannelSet::mono();
        REQUIRE_FALSE(mc::isSameInOut(l2));
    }

    SECTION("mono")
    {
        auto layout        = juce::AudioProcessor::BusesLayout {};
        layout.inputBuses  = juce::AudioChannelSet::mono();
        layout.outputBuses = juce::AudioChannelSet::mono();
        REQUIRE(mc::isSameInOut(layout));
    }

    SECTION("stereo")
    {
        auto layout        = juce::AudioProcessor::BusesLayout {};
        layout.inputBuses  = juce::AudioChannelSet::stereo();
        layout.outputBuses = juce::AudioChannelSet::stereo();
        REQUIRE(mc::isSameInOut(layout));
    }
}

TEST_CASE("audio_processors/processors: isStereoInOut", "[audio_processors]")
{
    SECTION("mono/stereo")
    {
        auto l1        = juce::AudioProcessor::BusesLayout {};
        l1.inputBuses  = juce::AudioChannelSet::mono();
        l1.outputBuses = juce::AudioChannelSet::stereo();
        REQUIRE_FALSE(mc::isStereoInOut(l1));

        auto l2        = juce::AudioProcessor::BusesLayout {};
        l2.inputBuses  = juce::AudioChannelSet::stereo();
        l2.outputBuses = juce::AudioChannelSet::mono();
        REQUIRE_FALSE(mc::isStereoInOut(l2));
    }

    SECTION("mono")
    {
        auto layout        = juce::AudioProcessor::BusesLayout {};
        layout.inputBuses  = juce::AudioChannelSet::mono();
        layout.outputBuses = juce::AudioChannelSet::mono();
        REQUIRE_FALSE(mc::isStereoInOut(layout));
    }

    SECTION("stereo")
    {
        auto layout        = juce::AudioProcessor::BusesLayout {};
        layout.inputBuses  = juce::AudioChannelSet::stereo();
        layout.outputBuses = juce::AudioChannelSet::stereo();
        REQUIRE(mc::isStereoInOut(layout));
    }
}
