#include <mc_gui_basics/mc_gui_basics.hpp>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_template_test_macros.hpp>

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
        pad.setXRange(juce::NormalisableRange<float> { 20.0F, 20'000.0F, 1.0F });
        CHECK(pad.getValueX() == Catch::Approx(20.0F));
        CHECK(pad.getNormalizedX() == Catch::Approx(0.0F));
        pad.setValueX(578.0F);
        CHECK(pad.getValueX() == Catch::Approx(578.0F));
        pad.setNormalizedX(0.5F);
        CHECK(pad.getValueX() == Catch::Approx(10010.0F));
        CHECK(pad.getNormalizedX() == Catch::Approx(0.5F));
    }

    SECTION("setY")
    {
        mc::XYPad pad {};
        pad.setYRange(juce::NormalisableRange<float> { 100.0F, 15'000.0F, 1.0F });
        CHECK(pad.getValueY() == 100.0F);
        CHECK(pad.getNormalizedY() == 0.0F);
        pad.setValueY(3244.0F);
        CHECK(pad.getValueY() == 3244.0F);
        pad.setNormalizedY(0.5F);
        CHECK(pad.getValueY() == Catch::Approx(7550.0F));
        CHECK(pad.getNormalizedY() == Catch::Approx(0.5F));
    }
}
