#include <mc_audio_processors/mc_audio_processors.hpp>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_template_test_macros.hpp>

TEST_CASE("audio_processors/text_value_converter: GainTextConverter", "[audio_processors]")
{
    SECTION("String -> float")
    {
        mc::GainTextConverter const converter {};
        REQUIRE(converter("0.0 db") == Catch::Approx(1.0F));
    }
    SECTION("String -> float")
    {
        mc::GainTextConverter const converter {};
        REQUIRE(converter("1.0 db") == Catch::Approx(1.12202F));
    }
    SECTION("String -> float")
    {
        mc::GainTextConverter const converter {};
        REQUIRE(converter("6.0 db") == Catch::Approx(1.99526F));
    }
}
