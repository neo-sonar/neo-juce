#include <mc_audio_processors/mc_audio_processors.hpp>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_template_test_macros.hpp>

TEST_CASE("audio_processors/text_value_converter: FrequencyTextConverter", "[audio_processors]")
{
    SECTION("String -> float")
    {
        mc::FrequencyTextConverter const converter {};
        REQUIRE(converter("10.00 Hz") == Catch::Approx(10.0F));
        REQUIRE(converter("10.00 kHz") == Catch::Approx(10000.0F));
    }

    SECTION("float -> String")
    {
        mc::FrequencyTextConverter const converter {};
        REQUIRE(converter(10.0F) == "10.00 Hz");
        REQUIRE(converter(10000.0F) == "10.00 kHz");
    }
}
