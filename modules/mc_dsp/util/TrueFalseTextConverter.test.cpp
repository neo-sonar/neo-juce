#include <mc_dsp/mc_dsp.hpp>

#include <catch2/catch_template_test_macros.hpp>

TEST_CASE("core/text: TrueFalseTextConverter", "[core]")
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
