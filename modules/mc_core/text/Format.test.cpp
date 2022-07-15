#include "mc_core/mc_core.hpp"

#include <catch2/catch_template_test_macros.hpp>

TEST_CASE("core/text: jformat", "")
{
    CHECK(mc::jformat(juce::String { "test" }) == "test");
    CHECK(mc::jformat(juce::String { "test{}" }, 143) == "test143");
    CHECK(mc::jformat(juce::String { "{}test" }, 143) == "143test");
    CHECK(mc::jformat(juce::String { "{0}test{0}" }, 143) == "143test143");
}
