#include <catch2/catch.hpp>

#include <mc_gui_basics/mc_gui_basics.hpp>

TEST_CASE("gui_basics/widget: XYPad", "")
{
    SECTION("default")
    {
        mc::XYPad pad {};
        CHECK(pad.getValueX() == 0);
        CHECK(pad.getValueY() == 0);
    }

    SECTION("setX")
    {
        mc::XYPad pad {};
        pad.setXRange(juce::NormalisableRange<float> { 20.0f, 20'000.0f, 1.0f });
        CHECK(pad.getValueX() == Approx(20.0f));
        CHECK(pad.getNormalizedX() == Approx(0.0f));
        pad.setValueX(578.0f);
        CHECK(pad.getValueX() == Approx(578.0f));
        pad.setNormalizedX(0.5f);
        CHECK(pad.getValueX() == Approx(10010.0f));
        CHECK(pad.getNormalizedX() == Approx(0.5f));
    }

    SECTION("setY")
    {
        mc::XYPad pad {};
        pad.setYRange(juce::NormalisableRange<float> { 100.0f, 15'000.0f, 1.0f });
        CHECK(pad.getValueY() == 100.0f);
        CHECK(pad.getNormalizedY() == 0.0f);
        pad.setValueY(3244.0f);
        CHECK(pad.getValueY() == 3244.0f);
        pad.setNormalizedY(0.5f);
        CHECK(pad.getValueY() == Approx(7550.0f));
        CHECK(pad.getNormalizedY() == Approx(0.5f));
    }
}