#include <mc_dsp/mc_dsp.hpp>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("dsp/units: barsToSamples", "[dsp]")
{
    REQUIRE(mc::barsToSamples(1.0, 240.0, 44'100.0) == Catch::Approx(44'100.0));
    REQUIRE(mc::barsToSamples(1.0, 120.0, 44'100.0) == Catch::Approx(88'200.0));
    REQUIRE(mc::barsToSamples(1.0, 120.0, 88'200.0) == Catch::Approx(176'400.0));

    REQUIRE(mc::barsToSamples(2.0, 120.0, 44'100.0) == Catch::Approx(176'400.0));
    REQUIRE(mc::barsToSamples(1.0 / 16.0, 240.0, 44'100.0) == Catch::Approx(2756.25));
    REQUIRE(mc::barsToSamples(1.0 / 8.0, 240.0, 44'100.0) == Catch::Approx(5512.5));
}

TEST_CASE("dsp/units: barsToSeconds", "[dsp]")
{
    REQUIRE(mc::barsToSeconds(120.0, 2.0, 1.0) == mc::Seconds<double> { 4.0 });
    REQUIRE(mc::barsToSeconds(120.0, 1.0, 1.0) == mc::Seconds<double> { 2.0 });
    REQUIRE(mc::barsToSeconds(120.0, 1.0, 4.0) == mc::Seconds<double> { 0.5 });
}

TEST_CASE("dsp/units: samplesToMicroseconds", "[dsp]")
{
    auto test = [](auto actual, auto expected) -> bool { return actual.count() == Catch::Approx(expected); };
    REQUIRE(test(mc::samplesToMicroseconds(44'100, 44'100.0), 1'000'000));
    REQUIRE(test(mc::samplesToMicroseconds(48'000, 48'000.0), 1'000'000));
    REQUIRE(test(mc::samplesToMicroseconds(88'200, 88'200.0), 1'000'000));
    REQUIRE(test(mc::samplesToMicroseconds(96'000, 96'000.0), 1'000'000));
    REQUIRE(test(mc::samplesToMicroseconds(22'050, 44'100.0), 500'000));
    REQUIRE(test(mc::samplesToMicroseconds(11'025, 44'100.0), 250'000));
}

TEST_CASE("dsp/units: samplesToMilliseconds", "[dsp]")
{
    auto test = [](auto actual, auto expected) -> bool { return actual.count() == Catch::Approx(expected); };
    REQUIRE(test(mc::samplesToMilliseconds(44'100, 44'100.0), 1'000));
    REQUIRE(test(mc::samplesToMilliseconds(48'000, 48'000.0), 1'000));
    REQUIRE(test(mc::samplesToMilliseconds(88'200, 88'200.0), 1'000));
    REQUIRE(test(mc::samplesToMilliseconds(96'000, 96'000.0), 1'000));
    REQUIRE(test(mc::samplesToMilliseconds(22'050, 44'100.0), 500));
    REQUIRE(test(mc::samplesToMilliseconds(11'025, 44'100.0), 250));
}

TEST_CASE("dsp/units: samplesToSeconds", "[dsp]")
{
    auto test = [](auto actual, auto expected) -> bool { return actual.count() == Catch::Approx(expected); };
    REQUIRE(test(mc::samplesToSeconds(44'100, 44'100.0), 1));
    REQUIRE(test(mc::samplesToSeconds(48'000, 48'000.0), 1));
    REQUIRE(test(mc::samplesToSeconds(88'200, 88'200.0), 1));
    REQUIRE(test(mc::samplesToSeconds(96'000, 96'000.0), 1));
    REQUIRE(test(mc::samplesToSeconds(22'050, 44'100.0), 0.5));
    REQUIRE(test(mc::samplesToSeconds(11'025, 44'100.0), 0.25));
}

TEST_CASE("dsp/units: toSampleCount(Microseconds)", "[dsp]")
{
    REQUIRE(mc::toSampleCount(mc::Microseconds<double> { 1'000'000 }, 44'100.0) == Catch::Approx(44'100));
    REQUIRE(mc::toSampleCount(mc::Microseconds<double> { 1'000'000 }, 48'000.0) == Catch::Approx(48'000));
    REQUIRE(mc::toSampleCount(mc::Microseconds<double> { 1'000'000 }, 88'200.0) == Catch::Approx(88'200));
    REQUIRE(mc::toSampleCount(mc::Microseconds<double> { 1'000'000 }, 96'000.0) == Catch::Approx(96'000));
    REQUIRE(mc::toSampleCount(mc::Microseconds<double> { 500'000 }, 44'100.0) == Catch::Approx(22'050));
    REQUIRE(mc::toSampleCount(mc::Microseconds<double> { 250'000 }, 44'100.0) == Catch::Approx(11'025));
}

TEST_CASE("dsp/units: toSampleCount(Milliseconds)", "[dsp]")
{
    REQUIRE(mc::toSampleCount(mc::Milliseconds<double> { 1'000 }, 44'100.0) == Catch::Approx(44'100));
    REQUIRE(mc::toSampleCount(mc::Milliseconds<double> { 1'000 }, 48'000.0) == Catch::Approx(48'000));
    REQUIRE(mc::toSampleCount(mc::Milliseconds<double> { 1'000 }, 88'200.0) == Catch::Approx(88'200));
    REQUIRE(mc::toSampleCount(mc::Milliseconds<double> { 1'000 }, 96'000.0) == Catch::Approx(96'000));
    REQUIRE(mc::toSampleCount(mc::Milliseconds<double> { 500 }, 44'100.0) == Catch::Approx(22'050));
    REQUIRE(mc::toSampleCount(mc::Milliseconds<double> { 250 }, 44'100.0) == Catch::Approx(11'025));
}

TEST_CASE("dsp/units: toSampleCount(Seconds)", "[dsp]")
{
    REQUIRE(mc::toSampleCount(mc::Seconds<double> { 1 }, 44'100.0) == Catch::Approx(44'100));
    REQUIRE(mc::toSampleCount(mc::Seconds<double> { 1 }, 48'000.0) == Catch::Approx(48'000));
    REQUIRE(mc::toSampleCount(mc::Seconds<double> { 1 }, 88'200.0) == Catch::Approx(88'200));
    REQUIRE(mc::toSampleCount(mc::Seconds<double> { 1 }, 96'000.0) == Catch::Approx(96'000));
    REQUIRE(mc::toSampleCount(mc::Seconds<double> { 0.5 }, 44'100.0) == Catch::Approx(22'050));
    REQUIRE(mc::toSampleCount(mc::Seconds<double> { 0.25 }, 44'100.0) == Catch::Approx(11'025));
}

TEMPLATE_TEST_CASE("dsp/units: bpmToHertz", "[dsp]", float, double)
{
    REQUIRE(mc::bpmToHertz(TestType(12.0)) == Catch::Approx(TestType(0.2)));
    REQUIRE(mc::bpmToHertz(TestType(60.0)) == Catch::Approx(TestType(1.0)));
    REQUIRE(mc::bpmToHertz(TestType(150.0)) == Catch::Approx(TestType(2.5)));
    REQUIRE(mc::bpmToHertz(TestType(120.0)) == Catch::Approx(TestType(2.0)));
    REQUIRE(mc::bpmToHertz(TestType(240.0)) == Catch::Approx(TestType(4.0)));
}
