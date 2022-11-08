#include <mc_lottie/mc_lottie.hpp>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("lottie/model: LottieColor::parse", "[lottie]")
{
    REQUIRE_THROWS(mc::LottieColor::parse(juce::JSON::parse("{}")));
    REQUIRE_THROWS(mc::LottieColor::parse(juce::JSON::parse("[0,0]")));

    auto const black = juce::JSON::parse("[0,0,0]");
    REQUIRE(mc::LottieColor::parse(black).red == Catch::Approx(0.0));
    REQUIRE(mc::LottieColor::parse(black).green == Catch::Approx(0.0));
    REQUIRE(mc::LottieColor::parse(black).blue == Catch::Approx(0.0));
    REQUIRE(mc::LottieColor::parse(black).alpha == Catch::Approx(1.0));

    auto const white = juce::JSON::parse("[1,1,1]");
    REQUIRE(mc::LottieColor::parse(white).red == Catch::Approx(1.0));
    REQUIRE(mc::LottieColor::parse(white).green == Catch::Approx(1.0));
    REQUIRE(mc::LottieColor::parse(white).blue == Catch::Approx(1.0));
    REQUIRE(mc::LottieColor::parse(white).alpha == Catch::Approx(1.0));

    auto const withAlpha = juce::JSON::parse("[0.0,0.25,0.5,0.75]");
    REQUIRE(mc::LottieColor::parse(withAlpha).red == Catch::Approx(0.0));
    REQUIRE(mc::LottieColor::parse(withAlpha).green == Catch::Approx(0.25));
    REQUIRE(mc::LottieColor::parse(withAlpha).blue == Catch::Approx(0.5));
    REQUIRE(mc::LottieColor::parse(withAlpha).alpha == Catch::Approx(0.75));

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
    REQUIRE(color.red == Catch::Approx(1.0));
    REQUIRE(color.green == Catch::Approx(0.98));
    REQUIRE(color.blue == Catch::Approx(0.28));
    REQUIRE(color.alpha == Catch::Approx(1.0));

    auto const property = mc::StaticLottieColor::parse(obj["c"]);
    REQUIRE(property.value.red == Catch::Approx(1.0));
    REQUIRE(property.value.green == Catch::Approx(0.98));
    REQUIRE(property.value.blue == Catch::Approx(0.28));
    REQUIRE(property.value.alpha == Catch::Approx(1.0));
}
