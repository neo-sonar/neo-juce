// SPDX-License-Identifier: BSL-1.0

#include <mcj_core/mcj_core.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("core/files: isZipFile", "[core]")
{
    auto cwd = juce::File::getCurrentWorkingDirectory();
    REQUIRE(mc::isZipFile(cwd.getChildFile("test_data/zip/one_file.zip")));
    REQUIRE_FALSE(mc::isZipFile(cwd.getChildFile("test_data/img/red_256x256.jpg")));
}
