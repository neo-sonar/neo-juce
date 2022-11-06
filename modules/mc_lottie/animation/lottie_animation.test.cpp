#include <mc_lottie/mc_lottie.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("lottie/animation: LottieAnimation::load(notfound.json)", "[lottie]")
{
    auto const cwd    = juce::File::getCurrentWorkingDirectory();
    auto const result = mc::LottieAnimation::load(cwd.getChildFile("test_data/lottie/notfound.json"));
    REQUIRE_FALSE(result.has_value());
}

TEST_CASE("lottie/animation: LottieAnimation::load(knob.json)", "[lottie]")
{
    auto const cwd    = juce::File::getCurrentWorkingDirectory();
    auto const result = mc::LottieAnimation::load(cwd.getChildFile("test_data/lottie/knob.json"));
    REQUIRE(result.has_value());

    auto const& model = result.value();
    REQUIRE(model.name == "Frame 2");
    REQUIRE(model.version == "5.9.6");
    REQUIRE(model.inPoint == 0);
    REQUIRE(model.outPoint == 120);
    REQUIRE(model.framerate == 60);
    REQUIRE(model.width == 150);
    REQUIRE(model.height == 150);
    REQUIRE(model.layers.size() == 10);
}

TEST_CASE("lottie/animation: LottieAnimation::load(bouncy_ball.json)", "[lottie]")
{
    auto const cwd    = juce::File::getCurrentWorkingDirectory();
    auto const result = mc::LottieAnimation::load(cwd.getChildFile("test_data/lottie/bouncy_ball.json"));
    REQUIRE(result.has_value());

    auto const& model = result.value();
    REQUIRE(model.name == "Bouncy Ball");
    REQUIRE(model.version == "5.5.2");
    REQUIRE(model.inPoint == 0);
    REQUIRE(model.outPoint == 120);
    REQUIRE(model.framerate == 60);
    REQUIRE(model.width == 512);
    REQUIRE(model.height == 512);
    REQUIRE(model.layers.size() == 1);

    auto const* layer = std::get_if<mc::LottieShapeLayer>(&model.layers[0]);
    REQUIRE(layer != nullptr);

    REQUIRE(layer->name == "Layer");
    REQUIRE(layer->inPoint == 0.0);
    REQUIRE(layer->outPoint == 120.0);

    REQUIRE(layer->transform.anchor.x == 0.0);
    REQUIRE(layer->transform.anchor.y == 0.0);

    REQUIRE(layer->transform.position.x == 0.0);
    REQUIRE(layer->transform.position.y == 0.0);

    REQUIRE(layer->transform.scale.x == 100.0);
    REQUIRE(layer->transform.scale.y == 100.0);

    REQUIRE(layer->shapes.size() == 1);
}
