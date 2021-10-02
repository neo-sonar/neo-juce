#include <mc_core/mc_core.hpp>

#include <catch2/catch.hpp>

TEST_CASE("core/time: toMilliseconds", "[core][time]")
{
    CHECK(mc::toMilliseconds(mc::Seconds { 1.0 }) == mc::Seconds { 1.0 });
    CHECK(mc::toMilliseconds(mc::Seconds { 1.0 }) == mc::Milliseconds { 1'000.0 });
    CHECK(mc::toMilliseconds(mc::Seconds { 0.5 }) == mc::Milliseconds { 500.0 });
}

TEST_CASE("core/time: toSeconds", "[core][time]")
{
    CHECK(mc::toSeconds(mc::Seconds { 1.0 }) == mc::Seconds { 1.0 });
    CHECK(mc::toSeconds(mc::Milliseconds { 1'000.0 }) == mc::Seconds { 1.0 });
    CHECK(mc::toSeconds(mc::Milliseconds { 500.0 }) == mc::Seconds { 0.5 });
}

TEST_CASE("core/time: VariantConverter<mc::Milliseconds>", "[core][time]")
{
    auto test = [](auto const& tc) -> bool {
        auto const var = juce::VariantConverter<mc::Milliseconds>::toVar(tc);
        return tc == juce::VariantConverter<mc::Milliseconds>::fromVar(var);
    };

    CHECK(test(mc::Milliseconds { 0.5 }));
    CHECK(test(mc::Milliseconds { 1.0 }));
    CHECK(test(mc::Milliseconds { 2.0 }));
}

TEST_CASE("core/time: VariantConverter<mc::Seconds>", "[core][time]")
{
    auto test = [](auto const& tc) -> bool {
        auto const var = juce::VariantConverter<mc::Seconds>::toVar(tc);
        return tc == juce::VariantConverter<mc::Seconds>::fromVar(var);
    };

    CHECK(test(mc::Seconds { 0.5 }));
    CHECK(test(mc::Seconds { 1.0 }));
    CHECK(test(mc::Seconds { 2.0 }));
}

TEST_CASE("core/time: VariantConverter<std::chrono::seconds>", "[core][time]")
{
    auto test = [](auto const& tc) -> bool {
        auto const var = juce::VariantConverter<std::chrono::seconds>::toVar(tc);
        return tc == juce::VariantConverter<std::chrono::seconds>::fromVar(var);
    };

    CHECK(test(std::chrono::seconds { 0 }));
    CHECK(test(std::chrono::seconds { 1 }));
    CHECK(test(std::chrono::seconds { 2 }));
}

TEST_CASE("core/time: VariantConverter<std::chrono::milliseconds>", "[core][time]")
{
    auto test = [](auto const& tc) -> bool {
        auto const var = juce::VariantConverter<std::chrono::milliseconds>::toVar(tc);
        return tc == juce::VariantConverter<std::chrono::milliseconds>::fromVar(var);
    };

    CHECK(test(std::chrono::milliseconds { 0 }));
    CHECK(test(std::chrono::milliseconds { 1 }));
    CHECK(test(std::chrono::milliseconds { 2 }));
}
