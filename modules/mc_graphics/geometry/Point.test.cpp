#include <mc_graphics/mc_graphics.hpp>

#include <catch2/catch_template_test_macros.hpp>

TEMPLATE_TEST_CASE("graphics/geometry: VariantConverter<juce::Point>", "[graphics]", int, float, double)
{
    auto convert = [](auto const& value) -> juce::Point<TestType> {
        auto const var = juce::VariantConverter<juce::Point<TestType>>::toVar(value);
        return juce::VariantConverter<juce::Point<TestType>>::fromVar(var);
    };

    auto const empty = juce::Point<TestType> {};
    REQUIRE(empty == convert(empty));

    auto const zero = juce::Point<TestType> { 0, 0 };
    REQUIRE(zero == convert(zero));

    auto const positive = juce::Point<TestType> { 75, 75 };
    REQUIRE(positive == convert(positive));

    auto const negative = juce::Point<TestType> { -25, -25 };
    REQUIRE(negative == convert(negative));
}
