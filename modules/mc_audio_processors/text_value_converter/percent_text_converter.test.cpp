#include <mc_audio_processors/mc_audio_processors.hpp>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_template_test_macros.hpp>

TEST_CASE("audio_processors/text_value_converter: PercentTextConverter", "[audio_processors]")
{
    SECTION("String -> float")
    {
        mc::PercentTextConverter const converter {};
        REQUIRE(converter("100.0 %") == 1.0F);
        REQUIRE(converter("0.0 %") == 0.0F);
        REQUIRE(converter("14.3 %") == 0.143F);
    }

    SECTION("float -> String")
    {
        mc::PercentTextConverter const converter {};
        REQUIRE(converter(0.0F) == "0.0 %");
        REQUIRE(converter(1.0F) == "100.0 %");
        REQUIRE(converter(0.143F) == "14.3 %");
    }
}
