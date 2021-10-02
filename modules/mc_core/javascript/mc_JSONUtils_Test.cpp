#include "mc_core/mc_core.hpp"

#include <catch2/catch.hpp>

TEST_CASE("core/javascript: JSONUtils::loadFromURL", "[core][javascript]")
{
    auto url  = juce::URL { "https://jsonplaceholder.typicode.com/users" };
    auto json = mc::JSONUtils::loadFromURL(url);
    CHECK(json.getArray()->size() == 10);
}
