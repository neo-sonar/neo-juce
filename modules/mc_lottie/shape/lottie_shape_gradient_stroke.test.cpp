#include <mc_lottie/mc_lottie.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("lottie/shape: LottieShapeGradientStroke::parse", "[lottie]")
{
    auto const* src = R"(
        {
          "ty": "gs",
          "o": { "a": 0, "k": 100 },
          "w": { "a": 0, "k": 6 },
          "g": {
            "p": 2,
            "k": {
              "a": 0,
              "k": [
                0, 1, 0.35294117647058826, 0.35294117647058826, 1, 1,
                0.5529411764705883, 0.35294117647058826, 0, 1, 1, 1
              ]
            }
          },
          "s": { "a": 0, "k": [139, -8.511295625466917e-15] },
          "e": { "a": 0, "k": [139, 138.99999999999997] },
          "t": 1,
          "lc": 1,
          "lj": 1,
          "ml": 0,
          "nm": "Stroke",
          "hd": false
        }
    )";

    auto reg       = entt::registry {};
    auto const obj = juce::JSON::parse(src);
    REQUIRE_NOTHROW(mc::LottieShape2::parse(reg, obj));
    SUCCEED();
}
