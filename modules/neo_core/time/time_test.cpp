// SPDX-License-Identifier: BSL-1.0

#include <neo_core/neo_core.hpp>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_template_test_macros.hpp>

TEST_CASE("core/time: VariantConverter<juce::Time>", "[core]")
{
    // SECTION("default")
    // {
    //     auto const time = juce::Time {};
    //     auto const var  = juce::VariantConverter<juce::Time>::toVar(time);
    //     REQUIRE(time == juce::VariantConverter<juce::Time>::fromVar(var));
    // }

    SECTION("constructed")
    {
        auto const time = juce::Time { 1995, 05, 15, 0, 0, 0, 0, false };
        auto const var  = juce::VariantConverter<juce::Time>::toVar(time);
        REQUIRE(time == juce::VariantConverter<juce::Time>::fromVar(var));
    }
}

TEST_CASE("core/time: VariantConverter<neo::Milliseconds>", "[core]")
{
    auto test = [](auto const& tc) {
        auto const var = juce::VariantConverter<neo::Milliseconds<double>>::toVar(tc);
        return juce::VariantConverter<neo::Milliseconds<double>>::fromVar(var);
    };

    REQUIRE(test(neo::Milliseconds<double> { 0.5 }).count() == Catch::Approx(0.5));
    REQUIRE(test(neo::Milliseconds<double> { 1.0 }).count() == Catch::Approx(1.0));
    REQUIRE(test(neo::Milliseconds<double> { 2.0 }).count() == Catch::Approx(2.0));
}

TEST_CASE("core/time: VariantConverter<neo::Seconds>", "[core]")
{
    auto test = [](auto const& tc) {
        auto const var = juce::VariantConverter<neo::Seconds<double>>::toVar(tc);
        return juce::VariantConverter<neo::Seconds<double>>::fromVar(var);
    };

    REQUIRE(test(neo::Seconds<double> { 0.5 }).count() == Catch::Approx(0.5));
    REQUIRE(test(neo::Seconds<double> { 1.0 }).count() == Catch::Approx(1.0));
    REQUIRE(test(neo::Seconds<double> { 2.0 }).count() == Catch::Approx(2.0));
}

TEST_CASE("core/time: VariantConverter<std::chrono::seconds>", "[core]")
{
    auto test = [](auto const& tc) -> bool {
        auto const var = juce::VariantConverter<std::chrono::seconds>::toVar(tc);
        return tc == juce::VariantConverter<std::chrono::seconds>::fromVar(var);
    };

    REQUIRE(test(std::chrono::seconds { 0 }));
    REQUIRE(test(std::chrono::seconds { 1 }));
    REQUIRE(test(std::chrono::seconds { 2 }));
}

TEST_CASE("core/time: VariantConverter<std::chrono::milliseconds>", "[core]")
{
    auto test = [](auto const& tc) -> bool {
        auto const var = juce::VariantConverter<std::chrono::milliseconds>::toVar(tc);
        return tc == juce::VariantConverter<std::chrono::milliseconds>::fromVar(var);
    };

    REQUIRE(test(std::chrono::milliseconds { 0 }));
    REQUIRE(test(std::chrono::milliseconds { 1 }));
    REQUIRE(test(std::chrono::milliseconds { 2 }));
}
