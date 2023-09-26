// SPDX-License-Identifier: BSL-1.0
#include <mc_extension_pack/mc_extension_pack.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("extension_pack/pack: validate(AssetLoader)", "[extension_pack]") // NOLINT
{
    using namespace mc;

    SECTION("empty")
    {
        auto loader = AssetLoader {};
        REQUIRE(validate(loader).failed());
        REQUIRE(validate(loader).getErrorMessage().contains("No search paths given"));
    }

    SECTION("no searcher")
    {
        auto loader = AssetLoader {
            /*.paths    = */ { juce::File {} },
            /*.searcher = */ nullptr,
            /*.transformer = */ nullptr,
        };
        REQUIRE(validate(loader).failed());
        REQUIRE(validate(loader).getErrorMessage().contains("No searcher given"));
    }

    SECTION("valid")
    {
        auto loader = AssetLoader {
            /*.paths    = */ { juce::File {} },
            /*.searcher = */ FileSearcher { "*.wav", true },
            /*.transformer = */ nullptr,
        };
        REQUIRE(static_cast<bool>(validate(loader)));
    }
}

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
            [](auto input) { return std::vector<std::byte>(begin(input), end(input)); },
        };
        REQUIRE_FALSE(build(builder).failed());
    }
}
