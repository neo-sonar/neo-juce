#include <mc_core/mc_core.hpp>

#include <catch2/catch_template_test_macros.hpp>

TEST_CASE("core/time: VariantConverter<mc::Milliseconds>", "")
{
    auto test = [](auto const& tc) -> bool {
        auto const var = juce::VariantConverter<mc::Milliseconds<double>>::toVar(tc);
        return tc == juce::VariantConverter<mc::Milliseconds<double>>::fromVar(var);
    };

    CHECK(test(mc::Milliseconds<double> { 0.5 }));
    CHECK(test(mc::Milliseconds<double> { 1.0 }));
    CHECK(test(mc::Milliseconds<double> { 2.0 }));
}

TEST_CASE("core/time: VariantConverter<mc::Seconds>", "")
{
    auto test = [](auto const& tc) -> bool {
        auto const var = juce::VariantConverter<mc::Seconds<double>>::toVar(tc);
        return tc == juce::VariantConverter<mc::Seconds<double>>::fromVar(var);
    };

    CHECK(test(mc::Seconds<double> { 0.5 }));
    CHECK(test(mc::Seconds<double> { 1.0 }));
    CHECK(test(mc::Seconds<double> { 2.0 }));
}

TEST_CASE("core/time: VariantConverter<std::chrono::seconds>", "")
{
    auto test = [](auto const& tc) -> bool {
        auto const var = juce::VariantConverter<std::chrono::seconds>::toVar(tc);
        return tc == juce::VariantConverter<std::chrono::seconds>::fromVar(var);
    };

    CHECK(test(std::chrono::seconds { 0 }));
    CHECK(test(std::chrono::seconds { 1 }));
    CHECK(test(std::chrono::seconds { 2 }));
}

TEST_CASE("core/time: VariantConverter<std::chrono::milliseconds>", "")
{
    auto test = [](auto const& tc) -> bool {
        auto const var = juce::VariantConverter<std::chrono::milliseconds>::toVar(tc);
        return tc == juce::VariantConverter<std::chrono::milliseconds>::fromVar(var);
    };

    CHECK(test(std::chrono::milliseconds { 0 }));
    CHECK(test(std::chrono::milliseconds { 1 }));
    CHECK(test(std::chrono::milliseconds { 2 }));
}
