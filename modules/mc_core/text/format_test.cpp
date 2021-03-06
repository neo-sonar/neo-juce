#include "mc_core/mc_core.hpp"

#include "catch2/catch_test_macros.hpp"

TEST_CASE("mc_core: format", "[core]")
{
    CHECK(mc::format(juce::String {"test"}) == "test");
    CHECK(mc::format(juce::String {"test{}"}, 143) == "test143");
    CHECK(mc::format(juce::String {"{}test"}, 143) == "143test");
    CHECK(mc::format(juce::String {"{0}test{0}"}, 143) == "143test143");
}
