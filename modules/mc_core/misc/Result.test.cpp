#include <mc_core/mc_core.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("core/misc: fail", "")
{
    auto result = mc::fail("error: {} and 42", juce::String { "foo" }, 42);
    REQUIRE(result.failed());
    REQUIRE(result.getErrorMessage() == "error: foo and 42");
}
