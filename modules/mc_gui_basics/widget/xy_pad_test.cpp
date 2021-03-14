#include "catch2/catch_approx.hpp"
#include "catch2/catch_test_macros.hpp"

#include <mc_gui_basics/mc_gui_basics.hpp>

TEST_CASE("gui_basics/widget: XYPad", "[gui_basics][widgets]")
{
    SECTION("default")
    {
        auto pad = mc::XYPad {};
        CHECK(pad.getXPosition() == 0);
        CHECK(pad.getYPosition() == 0);
    }

    SECTION("setX")
    {
        auto pad = mc::XYPad {};
        pad.setXRange(juce::NormalisableRange {20.0f, 20'000.0f, 1.0f});
        CHECK(pad.getXPosition() == Catch::Approx(20.0f));
        CHECK(pad.getNormalisedXPosition() == Catch::Approx(0.0f));
        pad.setXPosition(578.0f);
        CHECK(pad.getXPosition() == Catch::Approx(578.0f));
        pad.setNormalisedXPosition(0.5f);
        CHECK(pad.getXPosition() == Catch::Approx(10010.0f));
        CHECK(pad.getNormalisedXPosition() == Catch::Approx(0.5f));
    }

    SECTION("setY")
    {
        auto pad = mc::XYPad {};
        pad.setYRange(juce::NormalisableRange {100.0f, 15'000.0f, 1.0f});
        CHECK(pad.getYPosition() == 100.0f);
        CHECK(pad.getNormalisedYPosition() == 0.0f);
        pad.setYPosition(3244.0f);
        CHECK(pad.getYPosition() == 3244.0f);
        pad.setNormalisedYPosition(0.5f);
        CHECK(pad.getYPosition() == Catch::Approx(7550.0f));
        CHECK(pad.getNormalisedYPosition() == Catch::Approx(0.5f));
    }
}