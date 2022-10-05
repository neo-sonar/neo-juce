#include <mcj_extension_pack/mcj_extension_pack.hpp>

#include <catch2/catch_test_macros.hpp>

namespace {

} // namespace

TEST_CASE("extension_pack/pack: build(AssetLoader)", "[extension_pack]") // NOLINT
{
    using namespace mc;

    auto const spec = ExtensionPackSpecs { 1, { "dummy" } };

    SECTION("empty")
    {
        auto builder = ExtensionPackBuilder { spec, {} };
        REQUIRE(build(builder).failed());
        REQUIRE(build(builder).getErrorMessage().contains("No loaders registered"));
    }

    SECTION("validation failed")
    {
        auto builder             = ExtensionPackBuilder { spec, {} };
        builder.loaders["dummy"] = AssetLoader {};
        REQUIRE(build(builder).failed());
        REQUIRE(build(builder).getErrorMessage().contains("No search paths given"));
    }
}
