#include "lottie_model.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("lottie/model: LottieModel::load(not_found.json)", "[lottie]")
{
    auto const cwd = juce::File::getCurrentWorkingDirectory();
    REQUIRE_THROWS(mc::LottieModel::load(cwd.getChildFile("test_data/lottie/not_found.json")));

    auto const invalid = mc::LottieModel {};
    REQUIRE_THROWS(mc::name(invalid));
    REQUIRE_THROWS(mc::version(invalid));
    REQUIRE_THROWS(mc::inPoint(invalid));
    REQUIRE_THROWS(mc::outPoint(invalid));
    REQUIRE_THROWS(mc::width(invalid));
    REQUIRE_THROWS(mc::height(invalid));
    REQUIRE_THROWS(mc::framerate(invalid));
}

TEST_CASE("lottie/model: LottieModel::load(bouncy_ball.json)", "[lottie]")
{
    auto const cwd   = juce::File::getCurrentWorkingDirectory();
    auto const model = mc::LottieModel::load(cwd.getChildFile("test_data/lottie/bouncy_ball.json"));

    REQUIRE(mc::name(model) == "Bouncy Ball");
    REQUIRE(mc::version(model) == "5.5.2");
    REQUIRE(mc::inPoint(model) == 0.0);
    REQUIRE(mc::outPoint(model) == 120.0);
    REQUIRE(mc::width(model) == 512.0);
    REQUIRE(mc::height(model) == 512.0);
    REQUIRE(mc::framerate(model) == 60.0);
    // REQUIRE(model.layers.size() == 1);
}

TEST_CASE("lottie/model: LottieModel::load(knob.json)", "[lottie]")
{
    auto const cwd   = juce::File::getCurrentWorkingDirectory();
    auto const model = mc::LottieModel::load(cwd.getChildFile("test_data/lottie/knob.json"));

    REQUIRE(mc::name(model) == "Frame 2");
    REQUIRE(mc::version(model) == "5.9.6");
    REQUIRE(mc::inPoint(model) == 0.0);
    REQUIRE(mc::outPoint(model) == 120.0);
    REQUIRE(mc::framerate(model) == 60.0);
    REQUIRE(mc::width(model) == 150.0);
    REQUIRE(mc::height(model) == 150.0);
    // REQUIRE(model.layers.size() == 10);
}
