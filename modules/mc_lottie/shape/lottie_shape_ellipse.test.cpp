#include <mc_lottie/mc_lottie.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("lottie/shape: LottieShapeEllipse::parse", "[lottie]")
{
    auto const* src = R"(
        {
            "ty": "el",
            "nm": "Ellipse",
            "p": {
                "a": 0,
                "k": [
                    128,
                    256
                ]
            },
            "s": {
                "a": 0,
                "k": [
                    512,
                    1024
                ]
            }
        }
    )";

    auto reg         = entt::registry {};
    auto const obj   = juce::JSON::parse(src);
    auto const shape = mc::LottieShape::parse(reg, obj);
    REQUIRE(shape.type() == mc::LottieShapeType::ellipse);
    REQUIRE(shape.name() == "Ellipse");

    auto const ellipse = mc::tryGetComponent<mc::LottieShapeEllipse>(reg, shape.id);
    REQUIRE(ellipse.has_value());
    REQUIRE(ellipse->position.x == 128);
    REQUIRE(ellipse->position.y == 256);
    REQUIRE(ellipse->size.x == 512);
    REQUIRE(ellipse->size.y == 1024);
}
