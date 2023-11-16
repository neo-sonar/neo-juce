// SPDX-License-Identifier: BSL-1.0

#include <neo_core/neo_core.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("core/misc: fail", "[core]")
{
    auto result = neo::fail("error: {} and 42", juce::String { "foo" }, 42);
    REQUIRE(result.failed());
    REQUIRE(result.getErrorMessage() == "error: foo and 42");
}
