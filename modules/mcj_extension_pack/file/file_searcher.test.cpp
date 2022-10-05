#include <mcj_extension_pack/mcj_extension_pack.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("extension_pack/file: FileSearcher", "[extension_pack]") // NOLINT
{
    using namespace mc;

    SECTION("root directory does not exist")
    {
        auto searcher = FileSearcher { "*", false };
        REQUIRE(searcher(juce::File {}).empty());
    }

    SECTION("filter doesn't match")
    {
        auto searcher = FileSearcher { "*.wav", false };
        REQUIRE(searcher(makeFile("test_data/img")).empty());
    }

    SECTION("filter matches")
    {
        auto images = FileSearcher { "*.jpg", false };
        REQUIRE(images(makeFile("test_data/img")).size() == 1UL);

        auto all = FileSearcher { "*", false };
        REQUIRE(all(makeFile("test_data")).size() == 2UL);
    }
}
