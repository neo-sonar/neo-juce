#include <mc_lottie/mc_lottie.hpp>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("lottie/shape: LottieShapeFill::parse", "[lottie]")
{
    auto const* src = R"(
        {
            "ty": "fl",
            "nm": "Fill",
            "mn": "{3af40b83-15f6-4f69-aa2a-96acd03eb3b6}",
            "o": {
                "a": 0,
                "k": 100
            },
            "c": {
                "a": 0,
                "k": [
                    1,
                    0.98,
                    0.28
                ]
            },
            "r": 1
        }
    )";

    auto reg       = entt::registry {};
    auto const obj = juce::JSON::parse(src);

    auto const shape = mc::LottieShape::parse(reg, obj);
    REQUIRE(shape.type() == mc::LottieShapeType::fill);
    REQUIRE(shape.name() == "Fill");

    auto const color = mc::tryGetComponent<mc::StaticLottieColor>(reg, shape.id);
    REQUIRE(color.has_value());
    REQUIRE(color->value.red == 1.0);
    REQUIRE(color->value.green == Catch::Approx(0.98));
    REQUIRE(color->value.blue == Catch::Approx(0.28));
}
