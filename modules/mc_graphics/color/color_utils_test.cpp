#include <mc_graphics/mc_graphics.hpp>

#include "catch2/catch_test_macros.hpp"

TEST_CASE("mc_graphics/color: VariantConverter<juce::Colour>", "[graphics][color]")
{
    SECTION("black")
    {
        auto const color = juce::Colours::black;
        auto const var   = juce::VariantConverter<juce::Colour>::toVar(color);
        CHECK(color == juce::VariantConverter<juce::Colour>::fromVar(var));
    }

    SECTION("white")
    {
        auto const color = juce::Colours::white;
        auto const var   = juce::VariantConverter<juce::Colour>::toVar(color);
        CHECK(color == juce::VariantConverter<juce::Colour>::fromVar(var));
    }

    SECTION("pink")
    {
        auto const color = juce::Colours::pink;
        auto const var   = juce::VariantConverter<juce::Colour>::toVar(color);
        CHECK(color == juce::VariantConverter<juce::Colour>::fromVar(var));
    }
}