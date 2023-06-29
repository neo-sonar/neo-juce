#include <mc_extension_pack/mc_extension_pack.hpp>

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

        auto all = FileSearcher { "*.mid", true };
        REQUIRE(all(makeFile("test_data")).size() == 2UL);
    }
}

static constexpr auto const TestHeader = std::array<char, 8> { 'T', 'E', 'S', 'T', 'P', 'A', 'C', 'K' };

TEST_CASE("extension_pack/file: hasMagicHeader(std::span<char const>)", "[extension_pack]") // NOLINT
{
    using namespace mc;

    auto const zeros = std::array<char, 12> {};
    REQUIRE_FALSE(hasMagicHeader(zeros, TestHeader));
    REQUIRE_FALSE(hasMagicHeader(std::span<char const> {}, TestHeader));
    REQUIRE(hasMagicHeader(TestHeader, TestHeader));
}

TEST_CASE("extension_pack/file: hasMagicHeader(juce::InputStream)", "[extension_pack]") // NOLINT
{
    using namespace mc;

    SECTION("content to small")
    {
        auto out         = juce::MemoryOutputStream {};
        auto const dummy = std::array<char, 4> { 0, 1, 2, 3 };
        REQUIRE(out.write(dummy.data(), dummy.size()));
        REQUIRE_FALSE(hasMagicHeader(makeSpan(out), TestHeader));

        // Appending more content, does not change the outcome
        REQUIRE(out.writeDouble(42.0));
        REQUIRE_FALSE(hasMagicHeader(makeSpan(out), TestHeader));
    }

    SECTION("content matches")
    {
        auto out = juce::MemoryOutputStream {};
        REQUIRE(out.write(TestHeader.data(), TestHeader.size()));
        REQUIRE(hasMagicHeader(makeSpan(out), TestHeader));

        // Appending more content, does not change the outcome
        REQUIRE(out.writeDouble(42.0));
        REQUIRE(hasMagicHeader(makeSpan(out), TestHeader));
    }
}

TEST_CASE("extension_pack/file: hasMagicHeader(juce::File)", "[extension_pack]") // NOLINT
{
    using namespace mc;

    REQUIRE_FALSE(hasMagicHeader(juce::File {}, TestHeader));

    SECTION("content mismatch")
    {
        auto const tmp   = juce::TemporaryFile {};
        auto const& file = tmp.getFile();

        auto out = file.createOutputStream();
        REQUIRE(out != nullptr);

        auto const dummy = std::array<char, 4> { 0, 1, 2, 3 };
        REQUIRE(out->write(dummy.data(), dummy.size()));
        out.reset(nullptr); // flush to disk

        REQUIRE_FALSE(hasMagicHeader(file, TestHeader));
    }

    SECTION("content matches")
    {
        auto const tmp   = juce::TemporaryFile {};
        auto const& file = tmp.getFile();

        auto out = file.createOutputStream();
        REQUIRE(out != nullptr);

        REQUIRE(out->write(TestHeader.data(), TestHeader.size()));
        out.reset(nullptr);

        REQUIRE(hasMagicHeader(file, TestHeader));
    }

    SECTION("long magic header")
    {
        auto const longHeader = [] {
            auto arr = std::array<char, 1024> {};
            ranges::fill(arr, 42);
            return arr;
        }();

        auto const tmp   = juce::TemporaryFile {};
        auto const& file = tmp.getFile();

        auto out = file.createOutputStream();
        REQUIRE(out != nullptr);

        REQUIRE(out->write(longHeader.data(), longHeader.size()));
        out.reset(nullptr);

        REQUIRE(hasMagicHeader(file, longHeader));
    }
}
