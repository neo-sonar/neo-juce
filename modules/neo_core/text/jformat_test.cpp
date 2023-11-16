// SPDX-License-Identifier: BSL-1.0
#include <neo_core/neo_core.hpp>

#include <catch2/catch_template_test_macros.hpp>

TEST_CASE("core/text: format", "[core]")
{
    REQUIRE(fmt::format("{0}test{0}{1}", 143, juce::String { "foo" }) == "143test143foo");
}

TEST_CASE("core/text: jformat", "[core]")
{
    REQUIRE(neo::jformat("test") == "test");
    REQUIRE(neo::jformat("test{}", 143) == "test143");
    REQUIRE(neo::jformat("{}test", 143) == "143test");
    REQUIRE(neo::jformat("{0}test{0}", 143) == "143test143");
    REQUIRE(neo::jformat("{0}test{0}{1}", 143, juce::String { "foo" }) == "143test143foo");
}
