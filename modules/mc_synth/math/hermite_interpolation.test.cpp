#include <mc_synth/mc_synth.hpp>

#include <catch2/catch_template_test_macros.hpp>

TEMPLATE_TEST_CASE("synth/math: HermiteInterpolation", "[synth]", float, double) // NOLINT
{
    using T = TestType;
    using namespace mc;

    auto ip = HermiteInterpolation<T> {};

    auto zeros = std::array<T, 4> {};
    REQUIRE(ip(zeros, T {}) == T {});
    REQUIRE(ip(zeros, T { 1 }) == T {});
    REQUIRE(ip(zeros, static_cast<T>(0.5)) == T {});

    auto ones = std::array<T, 4> { 1, 1, 1, 1 };
    REQUIRE(ip(ones, T { 1 }) == T { 1 });
    REQUIRE(ip(ones, T { 1 }) == T { 1 });
    REQUIRE(ip(ones, static_cast<T>(0.5)) == T { 1 });
}

TEMPLATE_TEST_CASE("synth/math: samplesForHermiteInterpolation", "[synth]", int, unsigned, double) // NOLINT
{
    using T = TestType;
    using namespace mc;

    auto buffer = std::array<T, 4> { 1, 2, 3, 4 };
    REQUIRE(samplesForHermiteInterpolation<T>(buffer, 0) == std::array<T, 4> { 1, 1, 2, 3 });
    REQUIRE(samplesForHermiteInterpolation<T>(buffer, 1) == std::array<T, 4> { 1, 2, 3, 4 });
    REQUIRE(samplesForHermiteInterpolation<T>(buffer, 2) == std::array<T, 4> { 2, 3, 4, 1 });
    REQUIRE(samplesForHermiteInterpolation<T>(buffer, 3) == std::array<T, 4> { 3, 4, 1, 2 });
}
