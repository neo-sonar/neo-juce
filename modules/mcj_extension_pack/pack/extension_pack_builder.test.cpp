#include <mcj_extension_pack/mcj_extension_pack.hpp>

#include <catch2/catch_test_macros.hpp>

namespace {
struct TestPackSpec {
    static constexpr auto version = 1;
    enum struct AssetType { dummy };
};
} // namespace

TEST_CASE("extension_pack/pack: build(AssetLoader)", "[extension_pack]") // NOLINT
{
    using namespace mc;
    using Builder = ExtensionPackBuilder<TestPackSpec>;

    SECTION("empty")
    {
        auto builder = Builder {};
        REQUIRE(build(builder).failed());
        REQUIRE(build(builder).getErrorMessage().contains("No loaders registered"));
    }

    SECTION("validation failed")
    {
        auto builder                                    = Builder {};
        builder.loaders[TestPackSpec::AssetType::dummy] = AssetLoader {};
        REQUIRE(build(builder).failed());
        REQUIRE(build(builder).getErrorMessage().contains("No search paths given"));
    }
}
