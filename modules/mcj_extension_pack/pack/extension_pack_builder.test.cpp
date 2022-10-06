// SPDX-License-Identifier: BSL-1.0
#include <mcj_extension_pack/mcj_extension_pack.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("extension_pack/pack: build(AssetLoader)", "[extension_pack]") // NOLINT
{
    using namespace mc;

    auto const spec = ExtensionPackSpecs { 1, { "midi" } };

    SECTION("empty")
    {
        auto builder = ExtensionPackBuilder { spec, {} };
        REQUIRE(build(builder).failed());
        REQUIRE(build(builder).getErrorMessage().contains("No loaders registered"));
    }

    SECTION("validation failed")
    {
        auto builder            = ExtensionPackBuilder { spec, {} };
        builder.loaders["midi"] = AssetLoader {};
        REQUIRE(build(builder).failed());
        REQUIRE(build(builder).getErrorMessage().contains("No search paths given"));
    }

    SECTION("validation passed")
    {
        auto builder            = ExtensionPackBuilder { spec, {} };
        builder.loaders["midi"] = AssetLoader {
            { makeFile("test_data/midi") },
            FileSearcher { "*.mid", false },
            [](auto input) { return Vector<Byte>(begin(input), end(input)); },
        };
        REQUIRE_FALSE(build(builder).failed());
    }
}
