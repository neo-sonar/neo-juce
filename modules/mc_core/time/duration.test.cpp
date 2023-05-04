// SPDX-License-Identifier: BSL-1.0

#include <mc_core/mc_core.hpp>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_template_test_macros.hpp>

TEST_CASE("core/time: VariantConverter<mc::Milliseconds>", "[core]")
{
    auto test = [](auto const& tc)  {
        auto const var = juce::VariantConverter<mc::Milliseconds<double>>::toVar(tc);
        return juce::VariantConverter<mc::Milliseconds<double>>::fromVar(var);
    };

    REQUIRE(test(mc::Milliseconds<double> { 0.5 }).count() == Catch::Approx(0.5));
    REQUIRE(test(mc::Milliseconds<double> { 1.0 }).count() == Catch::Approx(1.0));
    REQUIRE(test(mc::Milliseconds<double> { 2.0 }).count() == Catch::Approx(2.0));
}

TEST_CASE("core/time: VariantConverter<mc::Seconds>", "[core]")
{
    auto test = [](auto const& tc)  {
        auto const var = juce::VariantConverter<mc::Seconds<double>>::toVar(tc);
        return juce::VariantConverter<mc::Seconds<double>>::fromVar(var);
    };

    REQUIRE(test(mc::Seconds<double> { 0.5 }).count() == Catch::Approx(0.5));
    REQUIRE(test(mc::Seconds<double> { 1.0 }).count() == Catch::Approx(1.0));
    REQUIRE(test(mc::Seconds<double> { 2.0 }).count() == Catch::Approx(2.0));
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
