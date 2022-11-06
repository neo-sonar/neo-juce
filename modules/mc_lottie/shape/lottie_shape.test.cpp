#include <mc_lottie/mc_lottie.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("lottie/shape: parseLottieShape(ellipse)", "[lottie]")
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

    auto const obj     = juce::JSON::parse(src);
    auto const shape   = mc::parseLottieShape(obj);
    auto const ellipse = std::get_if<mc::LottieShapeEllipse>(&shape);
    REQUIRE(ellipse != nullptr);
    REQUIRE(ellipse->name.has_value());
    REQUIRE(ellipse->name.value() == "Ellipse");
    REQUIRE(ellipse->position.x == 128);
    REQUIRE(ellipse->position.y == 256);
    REQUIRE(ellipse->size.x == 512);
    REQUIRE(ellipse->size.y == 1024);
}

TEST_CASE("lottie/shape: parseLottieShape(rectangle)", "[lottie]")
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

    auto const obj       = juce::JSON::parse(src);
    auto const shape     = mc::parseLottieShape(obj);
    auto const rectangle = std::get_if<mc::LottieShapeRectangle>(&shape);
    REQUIRE(rectangle != nullptr);
    REQUIRE(rectangle->name.has_value());
    REQUIRE(rectangle->name.value() == "Rectangle");
    REQUIRE(rectangle->position.x == 128);
    REQUIRE(rectangle->position.y == 256);
    REQUIRE(rectangle->size.x == 512);
    REQUIRE(rectangle->size.y == 1024);
    REQUIRE(rectangle->roundness == 10);
}
