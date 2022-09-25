#include <mcj_graphics/mcj_graphics.hpp>

#include <catch2/catch_template_test_macros.hpp>

TEMPLATE_TEST_CASE("graphics/geometry: VariantConverter<juce::Rectangle>", "[graphics]", int, float, double)
{
    auto convert = [](auto const& value) -> juce::Rectangle<TestType> {
        auto const var = juce::VariantConverter<juce::Rectangle<TestType>>::toVar(value);
        return juce::VariantConverter<juce::Rectangle<TestType>>::fromVar(var);
    };

    auto const empty = juce::Rectangle<TestType> {};
    REQUIRE(empty == convert(empty));

    auto const oneHundred = juce::Rectangle<TestType> { 0, 0, 100, 100 };
    REQUIRE(oneHundred == convert(oneHundred));

    auto const negative = juce::Rectangle<TestType> { -25, -25, 25, 25 };
    REQUIRE(negative == convert(negative));
}
