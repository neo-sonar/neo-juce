#include <mc_lottie/mc_lottie.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("lottie/shape: LottieShapeRectangle::parse", "[lottie]")
{
    auto const* src = R"(
        {
            "ty": "rc",
            "nm": "Rectangle",
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
            },
            "r": {
                "a": 0,
                "k": 10
            }
        }
    )";

    auto reg         = entt::registry {};
    auto const obj   = juce::JSON::parse(src);
    auto const shape = mc::LottieShape2::parse(reg, obj);
    REQUIRE(shape.type() == mc::LottieShapeType::rectangle);
    REQUIRE(shape.name() == "Rectangle");

    auto const rectangle = mc::tryGetComponent<mc::LottieShapeRectangle2>(reg, shape.id);
    REQUIRE(rectangle.has_value());
    REQUIRE(rectangle->position.x == 128);
    REQUIRE(rectangle->position.y == 256);
    REQUIRE(rectangle->size.x == 512);
    REQUIRE(rectangle->size.y == 1024);
    REQUIRE(rectangle->roundness == 10);
}
