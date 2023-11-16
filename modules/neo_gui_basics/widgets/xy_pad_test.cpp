#include <neo_gui_basics/neo_gui_basics.hpp>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_template_test_macros.hpp>

TEST_CASE("gui_basics/widget: XYPad", "[gui_basics]")
{
    SECTION("default")
    {
        neo::XYPad const pad {};
        REQUIRE(pad.getValueX() == Catch::Approx(0.0));
        REQUIRE(pad.getValueY() == Catch::Approx(0.0));
    }

    SECTION("setX")
    {
        neo::XYPad pad {};
        pad.setXRange(juce::NormalisableRange<float> { 20.0F, 20'000.0F, 1.0F });
        REQUIRE(pad.getValueX() == Catch::Approx(20.0F));
        REQUIRE(pad.getNormalizedX() == Catch::Approx(0.0F));
        pad.setValueX(578.0F);
        REQUIRE(pad.getValueX() == Catch::Approx(578.0F));
        pad.setNormalizedX(0.5F);
        REQUIRE(pad.getValueX() == Catch::Approx(10010.0F));
        REQUIRE(pad.getNormalizedX() == Catch::Approx(0.5F));
    }

    SECTION("setY")
    {
        neo::XYPad pad {};
        pad.setYRange(juce::NormalisableRange<float> { 100.0F, 15'000.0F, 1.0F });
        REQUIRE(pad.getValueY() == Catch::Approx(100.0));
        REQUIRE(pad.getNormalizedY() == Catch::Approx(0.0));
        pad.setValueY(3244.0F);
        REQUIRE(pad.getValueY() == Catch::Approx(3244.0));
        pad.setNormalizedY(0.5F);
        REQUIRE(pad.getValueY() == Catch::Approx(7550.0F));
        REQUIRE(pad.getNormalizedY() == Catch::Approx(0.5F));
    }
}
