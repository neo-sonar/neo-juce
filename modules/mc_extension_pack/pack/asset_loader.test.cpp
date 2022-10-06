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
