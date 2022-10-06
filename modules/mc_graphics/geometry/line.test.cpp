#include <mc_graphics/mc_graphics.hpp>

#include <catch2/catch_template_test_macros.hpp>

TEMPLATE_TEST_CASE("graphics/geometry: VariantConverter<juce::Line>", "[graphics]", int, float, double)
{
    auto convert = [](auto const& value) -> juce::Line<TestType> {
        auto const var = juce::VariantConverter<juce::Line<TestType>>::toVar(value);
        return juce::VariantConverter<juce::Line<TestType>>::fromVar(var);
    };

    auto const empty = juce::Line<TestType> {};
    REQUIRE(empty == convert(empty));

    auto const oneHundred = juce::Line<TestType> { 0, 0, 100, 100 };
    REQUIRE(oneHundred == convert(oneHundred));

    auto const negative = juce::Line<TestType> { -25, -25, 25, 25 };
    REQUIRE(negative == convert(negative));
}
