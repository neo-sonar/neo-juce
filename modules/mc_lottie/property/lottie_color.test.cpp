#include <mc_lottie/mc_lottie.hpp>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("lottie/model: LottieColor::parse", "[lottie]")
{
    REQUIRE(mc::LottieColor::parse(juce::JSON::parse("[0,0,0]")).red == 0.0);
    REQUIRE(mc::LottieColor::parse(juce::JSON::parse("[0,0,0]")).green == 0.0);
    REQUIRE(mc::LottieColor::parse(juce::JSON::parse("[0,0,0]")).blue == 0.0);

    REQUIRE(mc::LottieColor::parse(juce::JSON::parse("[1,1,1]")).red == 1.0);
    REQUIRE(mc::LottieColor::parse(juce::JSON::parse("[1,1,1]")).green == 1.0);
    REQUIRE(mc::LottieColor::parse(juce::JSON::parse("[1,1,1]")).blue == 1.0);

    auto const* src = R"(
        {
            "c": {
                "a": 0,
                "k": [
                    1,
                    0.98,
                    0.28
                ]
            }
        }
    )";

    auto const obj   = juce::JSON::parse(src);
    auto const color = mc::LottieColor::parse(obj["c"]["k"]);
    REQUIRE(color.red == 1.0);
    REQUIRE(color.green == Catch::Approx(0.98));
    REQUIRE(color.blue == Catch::Approx(0.28));

    auto const property = mc::StaticLottieColor::parse(obj["c"]);
    REQUIRE(property.value.red == 1.0);
    REQUIRE(property.value.green == Catch::Approx(0.98));
    REQUIRE(property.value.blue == Catch::Approx(0.28));
}
