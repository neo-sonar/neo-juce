#include <mc_core/mc_core.hpp>

#include "catch2/catch_approx.hpp"
#include "catch2/catch_template_test_macros.hpp"

TEST_CASE("core/time: VariantConverter<juce::Time>", "[core][time]")
{
    // SECTION("default")
    // {
    //     auto const time = juce::Time {};
    //     auto const var  = juce::VariantConverter<juce::Time>::toVar(time);
    //     CHECK(time == juce::VariantConverter<juce::Time>::fromVar(var));
    // }

    SECTION("constructed")
    {
        auto const time = juce::Time { 1995, 05, 15, 0, 0, 0, 0, false };
        auto const var  = juce::VariantConverter<juce::Time>::toVar(time);
        CHECK(time == juce::VariantConverter<juce::Time>::fromVar(var));
    }
}