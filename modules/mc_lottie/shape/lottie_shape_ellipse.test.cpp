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

    auto const obj     = juce::JSON::parse(src);
    auto const ellipse = mc::LottieShapeEllipse::parse(obj);
    REQUIRE(ellipse.name.has_value());
    REQUIRE(ellipse.name.value() == "Ellipse");
    REQUIRE(ellipse.position.x == 128);
    REQUIRE(ellipse.position.y == 256);
    REQUIRE(ellipse.size.x == 512);
    REQUIRE(ellipse.size.y == 1024);
}
