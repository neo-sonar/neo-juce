#include <mcj_audio_processors/mcj_audio_processors.hpp>

#include <catch2/catch_template_test_macros.hpp>

TEST_CASE("audio_processors/parameter: TrueFalseTextConverter", "[audio_processors]")
{
    SECTION("String -> float")
    {
        mc::TrueFalseTextConverter const converter {};
        REQUIRE(converter("true") > 0.5F);
        REQUIRE(converter("false") < 0.5F);
    }

    SECTION("float -> String")
    {
        mc::TrueFalseTextConverter const converter {};
        REQUIRE(converter(1.0F) == "true");
        REQUIRE(converter(0.0F) == "false");
    }
}
