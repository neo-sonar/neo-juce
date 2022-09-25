#include <mc_audio_processors/mc_audio_processors.hpp>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("audio_processors/attachment: XYPadAttachment", "[audio_processors]") // NOLINT
{
    mc::XYPad xypad {};
    REQUIRE(xypad.getXRange().start == Catch::Approx(0.0F));
    REQUIRE(xypad.getXRange().end == Catch::Approx(1.0F));

    REQUIRE(xypad.getValueX() == Catch::Approx(0.0F));
    REQUIRE(xypad.getValueY() == Catch::Approx(0.0F));

    xypad.setValueX(0.5F);
    xypad.setValueY(0.75F);
    REQUIRE(xypad.getValueX() == Catch::Approx(0.5F));
    REQUIRE(xypad.getValueY() == Catch::Approx(0.75F));

    juce::AudioParameterFloat paramA { "a", "a", 0.0F, 100.0F, 0.0F };
    juce::AudioParameterFloat paramB { "b", "b", 0.0F, 50.0F, 0.0F };

    mc::XYPadAttachment attachment { paramA, paramB, xypad, nullptr };
    REQUIRE(xypad.getXRange().start == Catch::Approx(0.0F));
    REQUIRE(xypad.getXRange().end == Catch::Approx(100.0F));
    REQUIRE(xypad.getYRange().start == Catch::Approx(0.0F));
    REQUIRE(xypad.getYRange().end == Catch::Approx(50.0F));

    REQUIRE(xypad.getValueX() == Catch::Approx(0.0F));
    REQUIRE(xypad.getValueY() == Catch::Approx(0.0F));

    paramA = 50.0F;
    paramB = 25.0F;
    REQUIRE(xypad.getValueX() == Catch::Approx(50.0F));
    REQUIRE(xypad.getValueY() == Catch::Approx(25.0F));
}
