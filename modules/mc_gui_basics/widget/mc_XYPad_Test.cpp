#include "catch2/catch_approx.hpp"
#include "catch2/catch_test_macros.hpp"

#include <mc_gui_basics/mc_gui_basics.hpp>

TEST_CASE("gui_basics/widget: XYPad", "[gui_basics][widgets]")
{
    SECTION("default")
    {
        auto pad = mc::XYPad {};
        CHECK(pad.getX() == 0);
        CHECK(pad.getY() == 0);
    }

    SECTION("setX")
    {
        auto pad = mc::XYPad {};
        pad.setXRange(juce::NormalisableRange {20.0f, 20'000.0f, 1.0f});
        CHECK(pad.getX() == Catch::Approx(20.0f));
        CHECK(pad.getNormalizedX() == Catch::Approx(0.0f));
        pad.setValueX(578.0f);
        CHECK(pad.getX() == Catch::Approx(578.0f));
        pad.setNormalizedX(0.5f);
        CHECK(pad.getX() == Catch::Approx(10010.0f));
        CHECK(pad.getNormalizedX() == Catch::Approx(0.5f));
    }

    SECTION("setY")
    {
        auto pad = mc::XYPad {};
        pad.setYRange(juce::NormalisableRange {100.0f, 15'000.0f, 1.0f});
        CHECK(pad.getY() == 100.0f);
        CHECK(pad.getNormalizedY() == 0.0f);
        pad.setValueY(3244.0f);
        CHECK(pad.getY() == 3244.0f);
        pad.setNormalizedY(0.5f);
        CHECK(pad.getY() == Catch::Approx(7550.0f));
        CHECK(pad.getNormalizedY() == Catch::Approx(0.5f));
    }
}