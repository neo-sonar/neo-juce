#include <mc_graphics/mc_graphics.hpp>

#include <catch2/catch.hpp>

TEMPLATE_TEST_CASE("graphics/geometry: VariantConverter<juce::Point>", "[graphics][geometry]", int, float, double)
{
    auto convert = [](auto const& value) -> juce::Point<TestType> {
        auto const var = juce::VariantConverter<juce::Point<TestType>>::toVar(value);
        return juce::VariantConverter<juce::Point<TestType>>::fromVar(var);
    };

    auto const empty = juce::Point<TestType> {};
    CHECK(empty == convert(empty));

    auto const zero = juce::Point<TestType> { 0, 0 };
    CHECK(zero == convert(zero));

    auto const positive = juce::Point<TestType> { 75, 75 };
    CHECK(positive == convert(positive));

    auto const negative = juce::Point<TestType> { -25, -25 };
    CHECK(negative == convert(negative));
}

TEMPLATE_TEST_CASE("graphics/geometry: VariantConverter<juce::Line>", "[graphics][geometry]", int, float, double)
{
    auto convert = [](auto const& value) -> juce::Line<TestType> {
        auto const var = juce::VariantConverter<juce::Line<TestType>>::toVar(value);
        return juce::VariantConverter<juce::Line<TestType>>::fromVar(var);
    };

    auto const empty = juce::Line<TestType> {};
    CHECK(empty == convert(empty));

    auto const oneHundred = juce::Line<TestType> { 0, 0, 100, 100 };
    CHECK(oneHundred == convert(oneHundred));

    auto const negative = juce::Line<TestType> { -25, -25, 25, 25 };
    CHECK(negative == convert(negative));
}

TEMPLATE_TEST_CASE("graphics/geometry: VariantConverter<juce::Rectangle>", "[graphics][geometry]", int, float, double)
{
    auto convert = [](auto const& value) -> juce::Rectangle<TestType> {
        auto const var = juce::VariantConverter<juce::Rectangle<TestType>>::toVar(value);
        return juce::VariantConverter<juce::Rectangle<TestType>>::fromVar(var);
    };

    auto const empty = juce::Rectangle<TestType> {};
    CHECK(empty == convert(empty));

    auto const oneHundred = juce::Rectangle<TestType> { 0, 0, 100, 100 };
    CHECK(oneHundred == convert(oneHundred));

    auto const negative = juce::Rectangle<TestType> { -25, -25, 25, 25 };
    CHECK(negative == convert(negative));
}
