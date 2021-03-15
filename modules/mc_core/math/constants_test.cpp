#include <mc_core/mc_core.hpp>

#include "catch2/catch_approx.hpp"
#include "catch2/catch_template_test_macros.hpp"

TEMPLATE_TEST_CASE("core/math: Euler", "[core][math]", float, double)
{
    REQUIRE(mc::Euler<TestType> == Catch::Approx(2.71828182845));
}

TEMPLATE_TEST_CASE("core/math: Pi", "[core][math]", float, double)
{
    REQUIRE(mc::Pi<TestType> == Catch::Approx(3.141592653));
}