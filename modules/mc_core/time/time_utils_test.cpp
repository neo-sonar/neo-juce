#include <mc_core/mc_core.hpp>

#include "catch2/catch_approx.hpp"
#include "catch2/catch_template_test_macros.hpp"

TEMPLATE_TEST_CASE("core/time: samplesToMicroseconds", "[core][time]", int, float, double)
{
    CHECK(mc::samplesToMicroseconds<TestType>(44'100, 44'100.0) == Catch::Approx(1'000'000));
    CHECK(mc::samplesToMicroseconds<TestType>(48'000, 48'000.0) == Catch::Approx(1'000'000));
    CHECK(mc::samplesToMicroseconds<TestType>(88'200, 88'200.0) == Catch::Approx(1'000'000));
    CHECK(mc::samplesToMicroseconds<TestType>(96'000, 96'000.0) == Catch::Approx(1'000'000));
    CHECK(mc::samplesToMicroseconds<TestType>(22'050, 44'100.0) == Catch::Approx(500'000));
    CHECK(mc::samplesToMicroseconds<TestType>(11'025, 44'100.0) == Catch::Approx(250'000));
}

TEMPLATE_TEST_CASE("core/time: samplesToMilliseconds", "[core][time]", int, float, double)
{
    CHECK(mc::samplesToMilliseconds<TestType>(44'100, 44'100.0) == Catch::Approx(1'000));
    CHECK(mc::samplesToMilliseconds<TestType>(48'000, 48'000.0) == Catch::Approx(1'000));
    CHECK(mc::samplesToMilliseconds<TestType>(88'200, 88'200.0) == Catch::Approx(1'000));
    CHECK(mc::samplesToMilliseconds<TestType>(96'000, 96'000.0) == Catch::Approx(1'000));
    CHECK(mc::samplesToMilliseconds<TestType>(22'050, 44'100.0) == Catch::Approx(500));
    CHECK(mc::samplesToMilliseconds<TestType>(11'025, 44'100.0) == Catch::Approx(250));
}

TEMPLATE_TEST_CASE("core/time: samplesToSeconds", "[core][time]", float, double)
{
    CHECK(mc::samplesToSeconds<TestType>(44'100, 44'100.0) == Catch::Approx(1));
    CHECK(mc::samplesToSeconds<TestType>(48'000, 48'000.0) == Catch::Approx(1));
    CHECK(mc::samplesToSeconds<TestType>(88'200, 88'200.0) == Catch::Approx(1));
    CHECK(mc::samplesToSeconds<TestType>(96'000, 96'000.0) == Catch::Approx(1));
    CHECK(mc::samplesToSeconds<TestType>(22'050, 44'100.0) == Catch::Approx(0.5));
    CHECK(mc::samplesToSeconds<TestType>(11'025, 44'100.0) == Catch::Approx(0.25));
}

TEMPLATE_TEST_CASE("core/time: microsecondsToSamples", "[core][time]", int, float, double)
{
    CHECK(mc::microsecondsToSamples<TestType>(1'000'000, 44'100.0) == Catch::Approx(44'100));
    CHECK(mc::microsecondsToSamples<TestType>(1'000'000, 48'000.0) == Catch::Approx(48'000));
    CHECK(mc::microsecondsToSamples<TestType>(1'000'000, 88'200.0) == Catch::Approx(88'200));
    CHECK(mc::microsecondsToSamples<TestType>(1'000'000, 96'000.0) == Catch::Approx(96'000));
    CHECK(mc::microsecondsToSamples<TestType>(500'000, 44'100.0) == Catch::Approx(22'050));
    CHECK(mc::microsecondsToSamples<TestType>(250'000, 44'100.0) == Catch::Approx(11'025));
}

TEMPLATE_TEST_CASE("core/time: millisecondsToSamples", "[core][time]", int, float, double)
{
    CHECK(mc::millisecondsToSamples<TestType>(1'000, 44'100.0) == Catch::Approx(44'100));
    CHECK(mc::millisecondsToSamples<TestType>(1'000, 48'000.0) == Catch::Approx(48'000));
    CHECK(mc::millisecondsToSamples<TestType>(1'000, 88'200.0) == Catch::Approx(88'200));
    CHECK(mc::millisecondsToSamples<TestType>(1'000, 96'000.0) == Catch::Approx(96'000));
    CHECK(mc::millisecondsToSamples<TestType>(500, 44'100.0) == Catch::Approx(22'050));
    CHECK(mc::millisecondsToSamples<TestType>(250, 44'100.0) == Catch::Approx(11'025));
}

TEMPLATE_TEST_CASE("core/time: secondsToSamples", "[core][time]", int, float, double)
{
    CHECK(mc::secondsToSamples<TestType>(1, 44'100.0) == Catch::Approx(44'100));
    CHECK(mc::secondsToSamples<TestType>(1, 48'000.0) == Catch::Approx(48'000));
    CHECK(mc::secondsToSamples<TestType>(1, 88'200.0) == Catch::Approx(88'200));
    CHECK(mc::secondsToSamples<TestType>(1, 96'000.0) == Catch::Approx(96'000));
    CHECK(mc::secondsToSamples<TestType>(0.5, 44'100.0) == Catch::Approx(22'050));
    CHECK(mc::secondsToSamples<TestType>(0.25, 44'100.0) == Catch::Approx(11'025));
}

TEST_CASE("core/time: barsToSamples", "[core][time]")
{
    CHECK(mc::barsToSamples(1.0, 240.0, 44'100.0) == Catch::Approx(44'100.0));
    CHECK(mc::barsToSamples(1.0, 120.0, 44'100.0) == Catch::Approx(88'200.0));
    CHECK(mc::barsToSamples(1.0, 120.0, 88'200.0) == Catch::Approx(176'400.0));

    CHECK(mc::barsToSamples(2.0, 120.0, 44'100.0) == Catch::Approx(176'400.0));
    CHECK(mc::barsToSamples(1.0 / 16.0, 240.0, 44'100.0) == Catch::Approx(2756.25));
    CHECK(mc::barsToSamples(1.0 / 8.0, 240.0, 44'100.0) == Catch::Approx(5512.5));
}

TEST_CASE("core/time: VariantConverter<juce::Time>", "[core][time]")
{
    SECTION("default")
    {
        auto const time = juce::Time {};
        auto const var  = juce::VariantConverter<juce::Time>::toVar(time);
        CHECK(time == juce::VariantConverter<juce::Time>::fromVar(var));
    }

    SECTION("constructed")
    {
        auto const time = juce::Time {1995, 05, 15, 0, 0, 0, 0, false};
        auto const var  = juce::VariantConverter<juce::Time>::toVar(time);
        CHECK(time == juce::VariantConverter<juce::Time>::fromVar(var));
    }
}