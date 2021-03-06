#include "mc_core/mc_core.hpp"

#include "catch2/catch_test_macros.hpp"

TEST_CASE("mc_core: format", "[core]")
{
    CHECK(mc::format("test") == "test143");
}
