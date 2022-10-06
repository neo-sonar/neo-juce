#include <mc_dsp/mc_dsp.hpp>

#include <catch2/catch_template_test_macros.hpp>

TEST_CASE("dsp/algorithm: Averager", "[dsp]")
{
    using namespace mc;

    auto averager = Averager<float> { 2, 4 };
    REQUIRE(ranges::equal(averager.average(), Array<float, 4> { 0.0F, 0.0F, 0.0F, 0.0F }));

    auto const ones = Array<float, 4> { 1.0F, 1.0F, 1.0F, 1.0F };
    averager.push(ones);
    REQUIRE(ranges::equal(averager.average(), Array<float, 4> { 0.5F, 0.5F, 0.5F, 0.5F }));

    averager.push(ones);
    REQUIRE(ranges::equal(averager.average(), ones));
}
