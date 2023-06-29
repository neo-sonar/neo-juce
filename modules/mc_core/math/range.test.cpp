// SPDX-License-Identifier: BSL-1.0

#include <mc_core/mc_core.hpp>

#include <catch2/catch_template_test_macros.hpp>

TEMPLATE_TEST_CASE("core/math: VariantConverter<juce::Range>", "[core]", int, float, double)
{
    SECTION("empty")
    {
        auto const range = juce::Range<TestType> {};
        auto const var   = juce::VariantConverter<juce::Range<TestType>>::toVar(range);
        REQUIRE(range == juce::VariantConverter<juce::Range<TestType>>::fromVar(var));
    }
    SECTION("0.0 - 10.0")
    {
        auto const range = juce::Range<TestType> { 0, 10 };
        auto const var   = juce::VariantConverter<juce::Range<TestType>>::toVar(range);
        REQUIRE(range == juce::VariantConverter<juce::Range<TestType>>::fromVar(var));
    }
    SECTION("-10.0 - 10.0")
    {
        auto const range = juce::Range<TestType> { -10, 10 };
        auto const var   = juce::VariantConverter<juce::Range<TestType>>::toVar(range);
        REQUIRE(range == juce::VariantConverter<juce::Range<TestType>>::fromVar(var));
    }
}

TEMPLATE_TEST_CASE("core/math: VariantConverter<juce::NormalisableRange>", "[core]", float, double)
{
    SECTION("empty")
    {
        auto const expected = juce::NormalisableRange<TestType> {};
        auto const var      = juce::VariantConverter<juce::NormalisableRange<TestType>>::toVar(expected);
        auto const testCase = juce::VariantConverter<juce::NormalisableRange<TestType>>::fromVar(var);

        REQUIRE(expected.start == Catch::Approx(testCase.start));
        REQUIRE(expected.end == Catch::Approx(testCase.end));
        REQUIRE(expected.interval == Catch::Approx(testCase.interval));
        REQUIRE(expected.skew == Catch::Approx(testCase.skew));
        REQUIRE(expected.symmetricSkew == testCase.symmetricSkew);
    }

    SECTION("0.0 - 10.0")
    {
        auto const expected = juce::NormalisableRange<TestType> { 0, 10 };
        auto const var      = juce::VariantConverter<juce::NormalisableRange<TestType>>::toVar(expected);
        auto const testCase = juce::VariantConverter<juce::NormalisableRange<TestType>>::fromVar(var);

        REQUIRE(expected.start == Catch::Approx(testCase.start));
        REQUIRE(expected.end == Catch::Approx(testCase.end));
        REQUIRE(expected.interval == Catch::Approx(testCase.interval));
        REQUIRE(expected.skew == Catch::Approx(testCase.skew));
        REQUIRE(expected.symmetricSkew == testCase.symmetricSkew);
    }
}
