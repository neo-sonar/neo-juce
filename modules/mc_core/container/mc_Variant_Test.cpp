#include "mc_core/mc_core.hpp"

#include "catch2/catch_test_macros.hpp"

TEST_CASE("core/container: variant", "[core][container]")
{
    auto v = mc::variant<int, float> { 143.0f };
    CHECK(mc::get<float>(v) == 143.0f);
}
