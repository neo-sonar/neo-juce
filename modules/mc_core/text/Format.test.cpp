#include "mc_core/mc_core.hpp"

#include <catch2/catch_template_test_macros.hpp>

TEST_CASE("core/text: format", "")
{
    CHECK(mc::format("{0}test{0}{1}", 143, juce::String { "foo" }) == "143test143foo");
}

TEST_CASE("core/text: jformat", "")
{
    CHECK(mc::jformat("test") == "test");
    CHECK(mc::jformat("test{}", 143) == "test143");
    CHECK(mc::jformat("{}test", 143) == "143test");
    CHECK(mc::jformat("{0}test{0}", 143) == "143test143");
    CHECK(mc::jformat("{0}test{0}{1}", 143, juce::String { "foo" }) == "143test143foo");
}
