#include "mc_core/mc_core.hpp"

#include "catch2/catch_template_test_macros.hpp"

TEMPLATE_TEST_CASE("mc_core: FlatMap::FlatMap()", "[core][container]", char, short, int, long long, float, double)
{
    SECTION("int key")
    {
        auto map = mc::FlatMap<int, TestType> {};
        CHECK(map.empty());
        CHECK(map.size() == 0);
    }

    SECTION("templated key")
    {
        auto map = mc::FlatMap<TestType, TestType> {};
        CHECK(map.empty());
        CHECK(map.size() == 0);
    }
}
