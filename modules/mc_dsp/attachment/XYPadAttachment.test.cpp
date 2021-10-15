#include <mc_dsp/mc_dsp.hpp>
#include <mc_gui_basics/mc_gui_basics.hpp>

#include <catch2/catch.hpp>

TEST_CASE("dsp/attachment: XYPadAttachment", "") // NOLINT
{
    mc::XYPad xypad {};
    CHECK(xypad.getXRange().start == Approx(0.0f));
    CHECK(xypad.getXRange().end == Approx(1.0f));

    CHECK(xypad.getValueX() == Approx(0.0f));
    CHECK(xypad.getValueY() == Approx(0.0f));

    xypad.setValueX(0.5f);
    xypad.setValueY(0.75f);
    CHECK(xypad.getValueX() == Approx(0.5f));
    CHECK(xypad.getValueY() == Approx(0.75f));

    juce::AudioParameterFloat paramA { "a", "a", 0.0f, 100.0f, 0.0f };
    juce::AudioParameterFloat paramB { "b", "b", 0.0f, 50.0f, 0.0f };

    mc::XYPadAttachment attachment { paramA, paramB, xypad, nullptr };
    CHECK(xypad.getXRange().start == Approx(0.0f));
    CHECK(xypad.getXRange().end == Approx(100.0f));
    CHECK(xypad.getYRange().start == Approx(0.0f));
    CHECK(xypad.getYRange().end == Approx(50.0f));

    CHECK(xypad.getValueX() == Approx(0.0f));
    CHECK(xypad.getValueY() == Approx(0.0f));

    paramA = 50.0f;
    paramB = 25.0f;
    CHECK(xypad.getValueX() == Approx(50.0f));
    CHECK(xypad.getValueY() == Approx(25.0f));
}