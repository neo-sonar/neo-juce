#include <mc_lottie/mc_lottie.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("lottie/model: LottieModel(not_found.json)", "[lottie]")
{
    auto const cwd = juce::File::getCurrentWorkingDirectory();
    REQUIRE_THROWS(mc::LottieModel::LottieModel(cwd.getChildFile("test_data/lottie/not_found.json")));
}

TEST_CASE("lottie/model: LottieModel(bouncy_ball.json)", "[lottie]")
{
    auto const cwd   = juce::File::getCurrentWorkingDirectory();
    auto const model = mc::LottieModel::LottieModel(cwd.getChildFile("test_data/lottie/bouncy_ball.json"));

    REQUIRE(model.name() == "Bouncy Ball");
    REQUIRE(model.version() == "5.5.2");
    REQUIRE(model.inPoint() == 0.0);
    REQUIRE(model.outPoint() == 120.0);
    REQUIRE(model.width() == 512.0);
    REQUIRE(model.height() == 512.0);
    REQUIRE(model.framerate() == 60.0);
    // REQUIRE(model.layers.size() == 1);
}

TEST_CASE("lottie/model: LottieModel(knob.json)", "[lottie]")
{
    auto const cwd   = juce::File::getCurrentWorkingDirectory();
    auto const model = mc::LottieModel::LottieModel(cwd.getChildFile("test_data/lottie/knob.json"));

    REQUIRE(model.name() == "Frame 2");
    REQUIRE(model.version() == "5.9.6");
    REQUIRE(model.inPoint() == 0.0);
    REQUIRE(model.outPoint() == 120.0);
    REQUIRE(model.framerate() == 60.0);
    REQUIRE(model.width() == 150.0);
    REQUIRE(model.height() == 150.0);
    // REQUIRE(model.layers.size() == 10);
}
