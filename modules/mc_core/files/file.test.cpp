// SPDX-License-Identifier: BSL-1.0

#include <mc_core/mc_core.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("core/files: format(juce::File)", "[core]")
{
    REQUIRE(mc::format("{}", juce::File {}) == "");
#if defined(MC_PLATFORM_WINDOWS)
    REQUIRE(mc::format("{}", juce::File { R"(C:\foo\bar\baz.txt)" }) == R"(C:\foo\bar\baz.txt)");
    REQUIRE(mc::format("{}", juce::File { "/foo/bar/baz.txt" }) == R"(C:\foo\bar\baz.txt)");
#else
    REQUIRE(mc::format("{}", juce::File { "/foo/bar/baz.txt" }) == "/foo/bar/baz.txt");
#endif
}

TEST_CASE("core/files: VariantConverter<juce::File>", "[core]")
{
    auto roundtrip = [](auto const& tc) -> bool {
        auto const var = juce::VariantConverter<juce::File>::toVar(tc);
        return tc == juce::VariantConverter<juce::File>::fromVar(var);
    };

    REQUIRE(roundtrip(juce::File {}));
    REQUIRE(roundtrip(juce::File { R"(C:\foo\bar\baz.txt)" }));
    REQUIRE(roundtrip(juce::File { "/foo/bar/baz.txt" }));
}

TEST_CASE("core/files: loadFileAsBytes", "[core]")
{
    using namespace mc;
    REQUIRE(loadFileAsBytes(juce::File {}).empty());
    REQUIRE_FALSE(loadFileAsBytes(makeFile("test_data/midi/130bpm_drum_beat.mid")).empty());
}

TEST_CASE("core/files: copyFile", "[core]")
{
    using namespace mc;
    REQUIRE(copyFile(juce::File { "/foo/does/no/exist" }, juce::File { "/bar/does/no/exist" }).failed());

    auto const testFile = makeFile("test_data/midi/130bpm_drum_beat.mid");
    REQUIRE(copyFile(juce::File {}, testFile).failed()); // src invalid
    REQUIRE(copyFile(testFile, juce::File {}).failed()); // dest invalid
}
