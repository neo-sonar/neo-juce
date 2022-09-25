#include <mcj_audio_processors/mcj_audio_processors.hpp>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_template_test_macros.hpp>

TEST_CASE("audio_processors/text_value_converter: SecondsTextConverter", "[audio_processors]")
{
    SECTION("String -> float")
    {
        mc::SecondsTextConverter const converter {};
        REQUIRE(converter("100.0 s") == 100.0F);
        REQUIRE(converter("0.00 s") == 0.0F);
        REQUIRE(converter("14.30 s") == 14.3F);
    }

    SECTION("float -> String")
    {
        mc::SecondsTextConverter const converter {};
        REQUIRE(converter(0.0F) == "0.00 s");
        REQUIRE(converter(1.0F) == "1.00 s");
        REQUIRE(converter(14.3F) == "14.30 s");
    }
}
