#include <mc_data_structures/mc_data_structures.hpp>

#include "catch2/catch_template_test_macros.hpp"
#include "catch2/catch_test_macros.hpp"

TEST_CASE("value_tree: VariantConverter<juce::Colour>", "[value_tree]")
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

TEMPLATE_TEST_CASE("value_tree: VariantConverter<juce::Range>", "[value_tree]", int, float, double)
{
    SECTION("empty")
    {
        auto const range = juce::Range<TestType> {};
        auto const var   = juce::VariantConverter<juce::Range<TestType>>::toVar(range);
        CHECK(range == juce::VariantConverter<juce::Range<TestType>>::fromVar(var));
    }
    SECTION("0.0 - 10.0")
    {
        auto const range = juce::Range<TestType> {0, 10};
        auto const var   = juce::VariantConverter<juce::Range<TestType>>::toVar(range);
        CHECK(range == juce::VariantConverter<juce::Range<TestType>>::fromVar(var));
    }
    SECTION("-10.0 - 10.0")
    {
        auto const range = juce::Range<TestType> {-10, 10};
        auto const var   = juce::VariantConverter<juce::Range<TestType>>::toVar(range);
        CHECK(range == juce::VariantConverter<juce::Range<TestType>>::fromVar(var));
    }
}

TEMPLATE_TEST_CASE("value_tree: VariantConverter<juce::NormalisableRange>", "[value_tree]", float, double)
{
    SECTION("empty")
    {
        auto const expected = juce::NormalisableRange<TestType> {};
        auto const var      = juce::VariantConverter<juce::NormalisableRange<TestType>>::toVar(expected);
        auto const testCase = juce::VariantConverter<juce::NormalisableRange<TestType>>::fromVar(var);

        CHECK(expected.start == testCase.start);
        CHECK(expected.end == testCase.end);
        CHECK(expected.interval == testCase.interval);
        CHECK(expected.skew == testCase.skew);
        CHECK(expected.symmetricSkew == testCase.symmetricSkew);
    }

    SECTION("0.0 - 10.0")
    {
        auto const expected = juce::NormalisableRange<TestType> {0, 10};
        auto const var      = juce::VariantConverter<juce::NormalisableRange<TestType>>::toVar(expected);
        auto const testCase = juce::VariantConverter<juce::NormalisableRange<TestType>>::fromVar(var);

        CHECK(expected.start == testCase.start);
        CHECK(expected.end == testCase.end);
        CHECK(expected.interval == testCase.interval);
        CHECK(expected.skew == testCase.skew);
        CHECK(expected.symmetricSkew == testCase.symmetricSkew);
    }
}

// TEST_CASE("value_tree: VariantConverter<juce::NormalisableRange<float>>", "[value_tree]")
//{
//    SECTION("defaultFrequencyRange")
//    {
//        auto const expected = mc::Ranges::defaultFrequencyRange();
//        auto const var      = juce::VariantConverter<juce::NormalisableRange<float>>::toVar(expected);
//        auto const testCase = juce::VariantConverter<juce::NormalisableRange<float>>::fromVar(var);
//
//        CHECK(expected.start == testCase.start);
//        CHECK(expected.end == testCase.end);
//        CHECK(expected.interval == testCase.interval);
//        CHECK(expected.skew == testCase.skew);
//        CHECK(expected.symmetricSkew == testCase.symmetricSkew);
//    }
//    SECTION("defaultTimeRange")
//    {
//        auto const expected = mc::Ranges::defaultTimeRange();
//        auto const var      = juce::VariantConverter<juce::NormalisableRange<float>>::toVar(expected);
//        auto const testCase = juce::VariantConverter<juce::NormalisableRange<float>>::fromVar(var);
//
//        CHECK(expected.start == testCase.start);
//        CHECK(expected.end == testCase.end);
//        CHECK(expected.interval == testCase.interval);
//        CHECK(expected.skew == testCase.skew);
//        CHECK(expected.symmetricSkew == testCase.symmetricSkew);
//    }
//}

TEMPLATE_TEST_CASE("value_tree: VariantConverter<juce::Point>", "[value_tree]", int, float, double)
{
    auto convert = [](auto const& value) -> juce::Point<TestType> {
        auto const var = juce::VariantConverter<juce::Point<TestType>>::toVar(value);
        return juce::VariantConverter<juce::Point<TestType>>::fromVar(var);
    };

    auto const empty = juce::Point<TestType> {};
    CHECK(empty == convert(empty));

    auto const zero = juce::Point<TestType> {0, 0};
    CHECK(zero == convert(zero));

    auto const positive = juce::Point<TestType> {75, 75};
    CHECK(positive == convert(positive));

    auto const negative = juce::Point<TestType> {-25, -25};
    CHECK(negative == convert(negative));
}

TEMPLATE_TEST_CASE("value_tree: VariantConverter<juce::Line>", "[value_tree]", int, float, double)
{
    auto convert = [](auto const& value) -> juce::Line<TestType> {
        auto const var = juce::VariantConverter<juce::Line<TestType>>::toVar(value);
        return juce::VariantConverter<juce::Line<TestType>>::fromVar(var);
    };

    auto const empty = juce::Line<TestType> {};
    CHECK(empty == convert(empty));

    auto const oneHundred = juce::Line<TestType> {0, 0, 100, 100};
    CHECK(oneHundred == convert(oneHundred));

    auto const negative = juce::Line<TestType> {-25, -25, 25, 25};
    CHECK(negative == convert(negative));
}

TEMPLATE_TEST_CASE("value_tree: VariantConverter<juce::Rectangle>", "[value_tree]", int, float, double)
{
    auto convert = [](auto const& value) -> juce::Rectangle<TestType> {
        auto const var = juce::VariantConverter<juce::Rectangle<TestType>>::toVar(value);
        return juce::VariantConverter<juce::Rectangle<TestType>>::fromVar(var);
    };

    auto const empty = juce::Rectangle<TestType> {};
    CHECK(empty == convert(empty));

    auto const oneHundred = juce::Rectangle<TestType> {0, 0, 100, 100};
    CHECK(oneHundred == convert(oneHundred));

    auto const negative = juce::Rectangle<TestType> {-25, -25, 25, 25};
    CHECK(negative == convert(negative));
}
