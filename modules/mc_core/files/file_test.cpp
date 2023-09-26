// SPDX-License-Identifier: BSL-1.0

#include <mc_core/mc_core.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("core/files: format(juce::File)", "[core]")
{
    REQUIRE(fmt::format("{}", juce::File {}).empty());

    // Can't run on Windows, since the CI runners use a different root
    // drive letter then most workstation installs. (C:\ vs. D:\)
#ifndef JUCE_WINDOWS
    REQUIRE(fmt::format("{}", juce::File { "/foo/bar/baz.txt" }) == "/foo/bar/baz.txt");
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
}

TEST_CASE("core/files: isZipFile", "[core]")
{
    auto cwd = juce::File::getCurrentWorkingDirectory();
    REQUIRE(mc::isZipFile(cwd.getChildFile("test_data/zip/one_file.zip")));
    REQUIRE_FALSE(mc::isZipFile(cwd.getChildFile("test_data/img/red_256x256.jpg")));
}
