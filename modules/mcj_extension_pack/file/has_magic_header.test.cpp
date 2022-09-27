#include <mcj_extension_pack/mcj_extension_pack.hpp>

#include <catch2/catch_test_macros.hpp>

static constexpr auto const testHeader = mc::Array<char, 8> { 'T', 'E', 'S', 'T', 'P', 'A', 'C', 'K' };

TEST_CASE("extension_pack/file: hasMagicHeader(Span<char const>)", "[extension_pack]") // NOLINT
{
    using namespace mc;

    auto const zeros = Array<char, 12> {};
    REQUIRE_FALSE(hasMagicHeader(zeros, testHeader));
    REQUIRE_FALSE(hasMagicHeader(Span<char const> {}, testHeader));
    REQUIRE(hasMagicHeader(testHeader, testHeader));
}

TEST_CASE("extension_pack/file: hasMagicHeader(juce::InputStream)", "[extension_pack]") // NOLINT
{
    using namespace mc;

    SECTION("content to small")
    {
        auto out         = juce::MemoryOutputStream {};
        auto const dummy = Array<char, 4> { 0, 1, 2, 3 };
        REQUIRE(out.write(dummy.data(), dummy.size()));
        REQUIRE_FALSE(hasMagicHeader(makeSpan(out), testHeader));

        // Appending more content, does not change the outcome
        REQUIRE(out.writeDouble(42.0));
        REQUIRE_FALSE(hasMagicHeader(makeSpan(out), testHeader));
    }

    SECTION("content matches")
    {
        auto out = juce::MemoryOutputStream {};
        REQUIRE(out.write(testHeader.data(), testHeader.size()));
        REQUIRE(hasMagicHeader(makeSpan(out), testHeader));

        // Appending more content, does not change the outcome
        REQUIRE(out.writeDouble(42.0));
        REQUIRE(hasMagicHeader(makeSpan(out), testHeader));
    }
}

TEST_CASE("extension_pack/file: hasMagicHeader(juce::File)", "[extension_pack]") // NOLINT
{
    using namespace mc;

    REQUIRE_FALSE(hasMagicHeader(juce::File {}, testHeader));

    SECTION("content mismatch")
    {
        auto const tmp   = juce::TemporaryFile {};
        auto const& file = tmp.getFile();

        auto out = file.createOutputStream();
        REQUIRE(out != nullptr);

        auto const dummy = Array<char, 4> { 0, 1, 2, 3 };
        REQUIRE(out->write(dummy.data(), dummy.size()));
        out.reset(nullptr); // flush to disk

        REQUIRE_FALSE(hasMagicHeader(file, testHeader));
    }

    SECTION("content matches")
    {
        auto const tmp   = juce::TemporaryFile {};
        auto const& file = tmp.getFile();

        auto out = file.createOutputStream();
        REQUIRE(out != nullptr);

        REQUIRE(out->write(testHeader.data(), testHeader.size()));
        out.reset(nullptr);

        REQUIRE(hasMagicHeader(file, testHeader));
    }

    SECTION("long magic header")
    {
        auto const longHeader = [] {
            auto arr = Array<char, 1024> {};
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
