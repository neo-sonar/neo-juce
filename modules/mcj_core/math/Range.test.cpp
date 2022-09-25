// SPDX-License-Identifier: BSL-1.0

#include <mcj_core/mcj_core.hpp>

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
