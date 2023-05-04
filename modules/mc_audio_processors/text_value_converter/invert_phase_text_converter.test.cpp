#include <mc_audio_processors/mc_audio_processors.hpp>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_template_test_macros.hpp>

TEST_CASE("audio_processors/text_value_converter: InvertPhaseTextConverter", "[audio_processors]")
{
    SECTION("String -> float")
    {
        mc::InvertPhaseTextConverter const converter {};
        REQUIRE(converter("Normal") == Catch::Approx(0.0F));
        REQUIRE(converter("Inverted") == Catch::Approx(1.0F));
    }

    SECTION("float -> String")
    {
        mc::InvertPhaseTextConverter const converter {};
        REQUIRE(converter(0.0F) == "Normal");
        REQUIRE(converter(1.0F) == "Inverted");
    }
}
