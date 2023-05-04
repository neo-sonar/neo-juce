#include <mc_audio_processors/mc_audio_processors.hpp>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_template_test_macros.hpp>

TEST_CASE("audio_processors/text_value_converter: MillisecondsTextConverter", "[audio_processors]")
{
    SECTION("String -> float")
    {
        mc::MillisecondsTextConverter const converter {};
        REQUIRE(converter("100.0 ms") == Catch::Approx(100.0F));
        REQUIRE(converter("0.0 ms") == Catch::Approx(0.0F));
        REQUIRE(converter("14.3 ms") == Catch::Approx(14.3F));
    }

    SECTION("float -> String")
    {
        mc::MillisecondsTextConverter const converter {};
        REQUIRE(converter(0.0F) == "0.0 ms");
        REQUIRE(converter(1.0F) == "1.0 ms");
        REQUIRE(converter(14.3F) == "14.3 ms");
    }
}
