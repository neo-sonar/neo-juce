#include <mc_lottie/mc_lottie.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("lottie/shape: LottieShapeTrim::parse", "[lottie]")
{
    auto const* src = R"(
        {
            "ty": "tm",
            "nm": "Trim Path",
            "mn": "{dcd7570f-5105-485b-bd43-42ad990b01e8}",
            "s": {
                "a": 0,
                "k": 0
            },
            "e": {
                "a": 0,
                "k": 50
            },
            "o": {
                "a": 0,
                "k": 0
            },
            "m": 1
        }
    )";

    auto reg       = entt::registry {};
    auto const obj = juce::JSON::parse(src);
    REQUIRE_NOTHROW(mc::LottieShape2::parse(reg, obj));
    SUCCEED();
}
