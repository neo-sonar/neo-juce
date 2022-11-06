#include <mc_lottie/mc_lottie.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("lottie/shape: LottieShapeTransform::parse", "[lottie]")
{
    auto const* src = R"(
        {
            "ty": "tr",
            "a": {
                "a": 0,
                "k": [
                    256,
                    256
                ]
            },
            "p": {
                "a": 0,
                "k": [
                    256,
                    256
                ]
            },
            "s": {
                "a": 0,
                "k": [
                    100,
                    100
                ]
            },
            "r": {
                "a": 0,
                "k": 0
            },
            "o": {
                "a": 0,
                "k": 100
            },
            "sk": {
                "a": 0,
                "k": 0
            },
            "sa": {
                "a": 0,
                "k": 0
            }
        }
    )";

    auto const obj = juce::JSON::parse(src);
    REQUIRE_NOTHROW(mc::LottieShapeTransform::parse(obj));
    SUCCEED();
}
