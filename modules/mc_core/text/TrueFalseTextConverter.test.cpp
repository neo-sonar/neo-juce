#include <mc_core/mc_core.hpp>

#include <catch2/catch_template_test_macros.hpp>

TEST_CASE("core/text: TrueFalseTextConverter", "[core]")
{
    SECTION("String -> float")
    {
        mc::TrueFalseTextConverter const converter {};
        REQUIRE(converter("true") == 1.0f);
        REQUIRE(converter("false") == 0.0f);
    }

    SECTION("float -> String")
    {
        mc::TrueFalseTextConverter const converter {};
        REQUIRE(converter(1.0f) == "true");
        REQUIRE(converter(0.0f) == "false");
    }
}
