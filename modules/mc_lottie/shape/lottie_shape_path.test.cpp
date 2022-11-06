#include <mc_lottie/mc_lottie.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("lottie/shape: LottieShapePath::parse", "[lottie]")
{
    auto const* src = R"(
        {
          "ty": "sh",
          "nm": "Path",
          "hd": false,
          "ks": {
            "a": 0,
            "k": {
              "c": true,
              "v": [
                [0, 150],
                [0, 0],
                [150, 0],
                [150, 150],
                [0, 150]
              ],
              "i": [
                [0, 0],
                [0, 0],
                [0, 0],
                [0, 0],
                [0, 0]
              ],
              "o": [
                [0, 0],
                [0, 0],
                [0, 0],
                [0, 0],
                [0, 0]
              ]
            }
          }
        },
    )";

    auto const obj = juce::JSON::parse(src);
    REQUIRE_NOTHROW(mc::LottieShapePath::parse(obj));
    SUCCEED();
}
