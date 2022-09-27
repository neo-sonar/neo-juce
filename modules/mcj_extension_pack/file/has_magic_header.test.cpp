#include <mcj_extension_pack/mcj_extension_pack.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("extension_pack/file: hasMagicHeader", "[extension_pack]") // NOLINT
{
    using namespace mc;

    static constexpr auto const magicHeader = Array<char, 8> { 'T', 'E', 'S', 'T', 'P', 'A', 'C', 'K' };

    SECTION("empty")
    {
        REQUIRE_FALSE(hasMagicHeader(juce::File {}, magicHeader));
        REQUIRE_FALSE(hasMagicHeader(Span<char const> {}, magicHeader));

        auto const zeros = Array<char, 12> {};
        REQUIRE_FALSE(hasMagicHeader(zeros, magicHeader));
    }

    SECTION("memory")
    {
        auto out = juce::MemoryOutputStream {};
        REQUIRE(out.write(magicHeader.data(), magicHeader.size()));
        REQUIRE(hasMagicHeader(makeSpan(out), magicHeader));

        REQUIRE(out.writeDouble(42.0));
        REQUIRE(hasMagicHeader(makeSpan(out), magicHeader));
    }

    SECTION("file")
    {
        auto const tmp   = juce::TemporaryFile {};
        auto const& file = tmp.getFile();

        auto out = file.createOutputStream();
        REQUIRE(out != nullptr);

        REQUIRE(out->write(magicHeader.data(), magicHeader.size()));
        out.reset(nullptr);

        REQUIRE(hasMagicHeader(file, magicHeader));
    }
}
