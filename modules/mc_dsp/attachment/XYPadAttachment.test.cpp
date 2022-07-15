#include <mc_dsp/mc_dsp.hpp>
#include <mc_gui_basics/mc_gui_basics.hpp>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_template_test_macros.hpp>

TEST_CASE("dsp/attachment: XYPadAttachment", "") // NOLINT
{
    mc::XYPad xypad {};
    CHECK(xypad.getXRange().start == Catch::Approx(0.0f));
    CHECK(xypad.getXRange().end == Catch::Approx(1.0f));

    CHECK(xypad.getValueX() == Catch::Approx(0.0f));
    CHECK(xypad.getValueY() == Catch::Approx(0.0f));

    xypad.setValueX(0.5f);
    xypad.setValueY(0.75f);
    CHECK(xypad.getValueX() == Catch::Approx(0.5f));
    CHECK(xypad.getValueY() == Catch::Approx(0.75f));

    juce::AudioParameterFloat paramA { "a", "a", 0.0f, 100.0f, 0.0f };
    juce::AudioParameterFloat paramB { "b", "b", 0.0f, 50.0f, 0.0f };

    mc::XYPadAttachment attachment { paramA, paramB, xypad, nullptr };
    CHECK(xypad.getXRange().start == Catch::Approx(0.0f));
    CHECK(xypad.getXRange().end == Catch::Approx(100.0f));
    CHECK(xypad.getYRange().start == Catch::Approx(0.0f));
    CHECK(xypad.getYRange().end == Catch::Approx(50.0f));

    CHECK(xypad.getValueX() == Catch::Approx(0.0f));
    CHECK(xypad.getValueY() == Catch::Approx(0.0f));

    paramA = 50.0f;
    paramB = 25.0f;
    CHECK(xypad.getValueX() == Catch::Approx(50.0f));
    CHECK(xypad.getValueY() == Catch::Approx(25.0f));
}