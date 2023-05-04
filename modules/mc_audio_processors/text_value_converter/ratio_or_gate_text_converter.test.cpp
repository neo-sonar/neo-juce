#include <mc_audio_processors/mc_audio_processors.hpp>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_template_test_macros.hpp>

TEST_CASE("audio_processors/text_value_converter: RatioOrGateTextConverter", "[audio_processors]")
{
    SECTION("String -> float")
    {
        mc::RatioOrGateTextConverter const converter {};
        REQUIRE(converter("100:1") == Catch::Approx(100.0F));
        REQUIRE(converter("1:1") == Catch::Approx(1.0F));
        REQUIRE(converter("14:1") == Catch::Approx(14.F));
        REQUIRE(converter("9.9:1") == Catch::Approx(9.9F));
    }

    SECTION("float -> String")
    {
        mc::RatioOrGateTextConverter const converter {};
        REQUIRE(converter(1.0F) == "1.0:1");
        REQUIRE(converter(11.0F) == "11:1");
        REQUIRE(converter(9.F) == "9.0:1");
        REQUIRE(converter(21.F) == "Gate");
    }
}
