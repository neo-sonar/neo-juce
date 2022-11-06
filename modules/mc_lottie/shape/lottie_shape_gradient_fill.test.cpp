#include <mc_lottie/mc_lottie.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("lottie/shape: LottieShapeGradientFill::parse", "[lottie]")
{
    auto const* src = R"(
        {
          "ty": "gf",
          "o": { "a": 0, "k": 100 },
          "g": {
            "p": 2,
            "k": {
              "a": 0,
              "k": [
                0, 0.26666666666666666, 0.26666666666666666,
                0.26666666666666666, 1, 0.4235294117647059, 0.4235294117647059,
                0.4235294117647059, 0, 1, 1, 1
              ]
            }
          },
          "s": { "a": 0, "k": [93, -5.6946078645210305e-15] },
          "e": { "a": 0, "k": [93, 92.99999999999999] },
          "t": 1,
          "nm": "Fill",
          "hd": false,
          "r": 1
        }
    )";

    auto const obj     = juce::JSON::parse(src);
    auto const ellipse = mc::LottieShapeGradientFill::parse(obj);
    SUCCEED();
}
