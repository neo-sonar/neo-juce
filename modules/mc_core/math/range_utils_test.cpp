#include <mc_core/mc_core.hpp>

#include "catch2/catch_template_test_macros.hpp"

TEMPLATE_TEST_CASE("mc_core/math: VariantConverter<juce::Range>", "[core][math]", int, float, double)
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

TEMPLATE_TEST_CASE("mc_core/math: VariantConverter<juce::NormalisableRange>", "[core][math]", float, double)
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

// TEST_CASE("mc_core/math: VariantConverter<juce::NormalisableRange<float>>", "[core][math]")
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