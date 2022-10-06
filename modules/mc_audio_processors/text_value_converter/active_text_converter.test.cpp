#include <mc_audio_processors/mc_audio_processors.hpp>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_template_test_macros.hpp>

TEST_CASE("audio_processors/text_value_converter: ActiveTextConverter", "[audio_processors]")
{
    SECTION("String -> float")
    {
        mc::ActiveTextConverter const converter {};
        REQUIRE(converter("active") == 1.0F);
        REQUIRE(converter("bypassed") == 0.0F);
    }

    SECTION("float -> String")
    {
        mc::ActiveTextConverter const converter {};
        REQUIRE(converter(1.0F) == "active");
        REQUIRE(converter(0.0F) == "bypassed");
    }
}
