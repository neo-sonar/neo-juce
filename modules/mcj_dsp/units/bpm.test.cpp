#include <mcj_dsp/mcj_dsp.hpp>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_template_test_macros.hpp>

TEMPLATE_TEST_CASE("dsp/units: bpmToHertz", "[dsp]", float, double)
{
    REQUIRE(mc::bpmToHertz(TestType(12.0)) == Catch::Approx(TestType(0.2)));
    REQUIRE(mc::bpmToHertz(TestType(60.0)) == Catch::Approx(TestType(1.0)));
    REQUIRE(mc::bpmToHertz(TestType(150.0)) == Catch::Approx(TestType(2.5)));
    REQUIRE(mc::bpmToHertz(TestType(120.0)) == Catch::Approx(TestType(2.0)));
    REQUIRE(mc::bpmToHertz(TestType(240.0)) == Catch::Approx(TestType(4.0)));
}
