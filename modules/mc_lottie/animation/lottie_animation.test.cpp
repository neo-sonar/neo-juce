#include <mc_lottie/mc_lottie.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("lottie/types: LottieAnimation", "[lottie]") // NOLINT
{
    using namespace mc;
    auto const cwd = juce::File::getCurrentWorkingDirectory();

    SECTION("invalid file path")
    {
        auto result = loadLottieAnimation(cwd.getChildFile("test_data/lottie/notfound.json"));
        REQUIRE_FALSE(result.has_value());
    }

    SECTION("knob")
    {
        auto result = loadLottieAnimation(cwd.getChildFile("test_data/lottie/lottie_knob.json"));
        REQUIRE(result.has_value());

        auto model = result.value();
        REQUIRE(model.name == "Frame 2");
        REQUIRE(model.version == "5.9.6");
        REQUIRE(model.inPoint == 0);
        REQUIRE(model.outPoint == 120);
        REQUIRE(model.framerate == 60);
        REQUIRE(model.width == 150);
        REQUIRE(model.height == 150);
        REQUIRE(model.layers.size() == 10);
    }
}
