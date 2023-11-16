// SPDX-License-Identifier: BSL-1.0
#include <neo_core/neo_core.hpp>

#include <catch2/catch_template_test_macros.hpp>

TEST_CASE("core/javascript: JSONUtils::loadFromURL", "[core]")
{
    auto url  = juce::URL { "https://jsonplaceholder.typicode.com/users" };
    auto json = neo::JSONUtils::loadFromURL(url);
    REQUIRE(json.getArray()->size() == 10);
}
