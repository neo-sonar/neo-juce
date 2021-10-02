#include <mc_core/mc_core.hpp>

#include <catch2/catch.hpp>

TEMPLATE_TEST_CASE("core/math: Euler", "[core][math]", float, double)
{
    REQUIRE(mc::Euler<TestType> == Approx(2.71828182845));
}

TEMPLATE_TEST_CASE("core/math: Pi", "[core][math]", float, double)
{
    REQUIRE(mc::Pi<TestType> == Approx(3.141592653));
}