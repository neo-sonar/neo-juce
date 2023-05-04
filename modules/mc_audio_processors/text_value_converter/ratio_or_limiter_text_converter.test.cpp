#include <mc_audio_processors/mc_audio_processors.hpp>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_template_test_macros.hpp>

TEST_CASE("audio_processors/text_value_converter: RatioOrLimiterTextConverter", "[audio_processors]")
{
    SECTION("String -> float")
    {
        mc::RatioOrLimiterTextConverter const converter {};
        REQUIRE(converter("1:100") == Catch::Approx(100.0F));
        REQUIRE(converter("1:1.0") == Catch::Approx(1.0F));
        REQUIRE(converter("1:14") == Catch::Approx(14.F));
        REQUIRE(converter("1:9.9") == Catch::Approx(9.9F));
    }

    SECTION("float -> String")
    {
        mc::RatioOrLimiterTextConverter const converter {};
        REQUIRE(converter(1.0F) == "1:1.0");
        REQUIRE(converter(11.0F) == "1:11");
        REQUIRE(converter(9.F) == "1:9.0");
        REQUIRE(converter(30.1F) == "Limiter");
    }
}
