#include <mcj_audio_processors/mcj_audio_processors.hpp>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_template_test_macros.hpp>

TEST_CASE("audio_processors/text_value_converter: QualityTextConverter", "[audio_processors]")
{
    SECTION("String -> float")
    {
        mc::QualityTextConverter const converter {};
        REQUIRE(converter("1.2") == 1.2F);
        REQUIRE(converter("0.0") == 0.0F);
    }

    SECTION("float -> String")
    {
        mc::QualityTextConverter const converter {};
        REQUIRE(converter(1.0F) == "1.0");
        REQUIRE(converter(0.24F) == "0.2");
        REQUIRE(converter(9.99F) == "10.0");
    }
}
