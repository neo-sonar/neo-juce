#include <mc_lottie/mc_lottie.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("lottie/animation: loadLottieAnimation(notfound.json)", "[lottie]")
{
    auto const cwd    = juce::File::getCurrentWorkingDirectory();
    auto const result = mc::loadLottieAnimation(cwd.getChildFile("test_data/lottie/notfound.json"));
    REQUIRE_FALSE(result.has_value());
}

TEST_CASE("lottie/animation: loadLottieAnimation(knob.json)", "[lottie]")
{
    auto const cwd    = juce::File::getCurrentWorkingDirectory();
    auto const result = mc::loadLottieAnimation(cwd.getChildFile("test_data/lottie/knob.json"));
    REQUIRE(result.has_value());

    auto const model = result.value();
    REQUIRE(model.name == "Frame 2");
    REQUIRE(model.version == "5.9.6");
    REQUIRE(model.inPoint == 0);
    REQUIRE(model.outPoint == 120);
    REQUIRE(model.framerate == 60);
    REQUIRE(model.width == 150);
    REQUIRE(model.height == 150);
    REQUIRE(model.layers.size() == 10);
}

TEST_CASE("lottie/animation: loadLottieAnimation(bouncy_ball.json)", "[lottie]")
{
    auto const cwd    = juce::File::getCurrentWorkingDirectory();
    auto const result = mc::loadLottieAnimation(cwd.getChildFile("test_data/lottie/bouncy_ball.json"));
    REQUIRE(result.has_value());

    auto const model = result.value();
    REQUIRE(model.name == "Bouncy Ball");
    REQUIRE(model.version == "5.5.2");
    REQUIRE(model.inPoint == 0);
    REQUIRE(model.outPoint == 120);
    REQUIRE(model.framerate == 60);
    REQUIRE(model.width == 512);
    REQUIRE(model.height == 512);
    REQUIRE(model.layers.size() == 1);

    auto const layer = model.layers[0];
    REQUIRE(mc::name(layer) == "Layer");
    REQUIRE(mc::inPoint(layer) == 0.0);
    REQUIRE(mc::outPoint(layer) == 120.0);
}
