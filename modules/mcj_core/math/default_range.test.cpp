// SPDX-License-Identifier: BSL-1.0

#include <mcj_core/mcj_core.hpp>

#include <catch2/catch_template_test_macros.hpp>

TEMPLATE_TEST_CASE("core/math: DefaultRange::normalized", "[core]", float, double)
{
    auto const normalized = mc::DefaultRange<float>::normalized();
    REQUIRE(normalized.start == TestType(0));
    REQUIRE(normalized.end == TestType(1));
}

TEMPLATE_TEST_CASE("core/math: DefaultRange::gain", "[core]", float, double)
{
    auto const gain = mc::DefaultRange<float>::gain();
    REQUIRE(gain.start == TestType(0));
    REQUIRE(gain.end == TestType(4));
}

TEMPLATE_TEST_CASE("core/math: DefaultRange::frequency", "[core]", float, double)
{
    auto const frequency = mc::DefaultRange<float>::frequency();
    REQUIRE(frequency.start == TestType(20));
    REQUIRE(frequency.end == TestType(20000));
}

TEMPLATE_TEST_CASE("core/math: DefaultRange::timeMilliseconds", "[core]", float, double)
{
    auto const timeMilliseconds = mc::DefaultRange<float>::timeMilliseconds();
    REQUIRE(timeMilliseconds.start == TestType(0));
    REQUIRE(timeMilliseconds.end == TestType(2000));
}
