#include <mc_core/mc_core.hpp>

#include <catch2/catch_template_test_macros.hpp>

TEMPLATE_TEST_CASE("core/math: VariantConverter<juce::NormalisableRange>", "", float, double)
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
        auto const expected = juce::NormalisableRange<TestType> { 0, 10 };
        auto const var      = juce::VariantConverter<juce::NormalisableRange<TestType>>::toVar(expected);
        auto const testCase = juce::VariantConverter<juce::NormalisableRange<TestType>>::fromVar(var);

        CHECK(expected.start == testCase.start);
        CHECK(expected.end == testCase.end);
        CHECK(expected.interval == testCase.interval);
        CHECK(expected.skew == testCase.skew);
        CHECK(expected.symmetricSkew == testCase.symmetricSkew);
    }
}
