#include <mc_core/mc_core.hpp>

#include <catch2/catch.hpp>

TEST_CASE("core/text: ActiveTextConverter", "[core][text]")
{
    SECTION("String -> float")
    {
        mc::ActiveTextConverter const converter {};
        REQUIRE(converter("active") == 1.0f);
        REQUIRE(converter("bypassed") == 0.0f);
    }

    SECTION("float -> String")
    {
        mc::ActiveTextConverter const converter {};
        REQUIRE(converter(1.0f) == "active");
        REQUIRE(converter(0.0f) == "bypassed");
    }
}

TEST_CASE("core/text: FrequencyTextConverter", "[core][text]")
{
    SECTION("String -> float")
    {
        mc::FrequencyTextConverter const converter {};
        REQUIRE(converter("10 Hz") == 10.0f);
        REQUIRE(converter("10.00 kHz") == 10000.0f);
    }

    SECTION("float -> String")
    {
        mc::FrequencyTextConverter const converter {};
        REQUIRE(converter(10.0f) == "10 Hz");
        REQUIRE(converter(10000.0f) == "10.00 kHz");
    }
}

TEST_CASE("core/text: QualityTextConverter", "[core][text]")
{
    SECTION("String -> float")
    {
        mc::QualityTextConverter const converter {};
        REQUIRE(converter("1.2") == 1.2f);
        REQUIRE(converter("0.0") == 0.0f);
    }

    SECTION("float -> String")
    {
        mc::QualityTextConverter const converter {};
        REQUIRE(converter(1.0f) == "1.0");
        REQUIRE(converter(0.24f) == "0.2");
        REQUIRE(converter(9.99f) == "10.0");
    }
}

TEST_CASE("core/text: GainTextConverter", "[core][text]")
{
    SECTION("String -> float")
    {
        mc::GainTextConverter const converter {};
        REQUIRE(converter("0.0 db") == Approx(1.0f));
    }
    SECTION("String -> float")
    {
        mc::GainTextConverter const converter {};
        REQUIRE(converter("1.0 db") == Approx(1.12202f));
    }
    SECTION("String -> float")
    {
        mc::GainTextConverter const converter {};
        REQUIRE(converter("6.0 db") == Approx(1.99526f));
    }
}

TEST_CASE("core/text: PercentTextConverter", "[core][text]")
{
    SECTION("String -> float")
    {
        mc::PercentTextConverter const converter {};
        REQUIRE(converter("100.0 %") == 1.0f);
        REQUIRE(converter("0.0 %") == 0.0f);
        REQUIRE(converter("14.3 %") == 0.143f);
    }

    SECTION("float -> String")
    {
        mc::PercentTextConverter const converter {};
        REQUIRE(converter(0.0f) == "0.0 %");
        REQUIRE(converter(1.0f) == "100.0 %");
        REQUIRE(converter(0.143f) == "14.3 %");
    }
}

TEST_CASE("core/text: TimeSecondsTextConverter", "[core][text]")
{
    SECTION("String -> float")
    {
        mc::TimeSecondsTextConverter const converter {};
        REQUIRE(converter("100.0 s") == 100.0f);
        REQUIRE(converter("0.00 s") == 0.0f);
        REQUIRE(converter("14.30 s") == 14.3f);
    }

    SECTION("float -> String")
    {
        mc::TimeSecondsTextConverter const converter {};
        REQUIRE(converter(0.0f) == "0.00 s");
        REQUIRE(converter(1.0f) == "1.00 s");
        REQUIRE(converter(14.3f) == "14.30 s");
    }
}

TEST_CASE("core/text: TimeMillisecondsTextConverter", "[core][text]")
{
    SECTION("String -> float")
    {
        mc::TimeMillisecondsTextConverter const converter {};
        REQUIRE(converter("100.0 ms") == 100.0f);
        REQUIRE(converter("0.0 ms") == 0.0f);
        REQUIRE(converter("14.3 ms") == 14.3f);
    }

    SECTION("float -> String")
    {
        mc::TimeMillisecondsTextConverter const converter {};
        REQUIRE(converter(0.0f) == "0.0 ms");
        REQUIRE(converter(1.0f) == "1.0 ms");
        REQUIRE(converter(14.3f) == "14.3 ms");
    }
}

TEST_CASE("core/text: RatioCompTextConverter", "[core][text]")
{
    SECTION("String -> float")
    {
        mc::RatioCompTextConverter const converter {};
        REQUIRE(converter("1:100") == 100.0f);
        REQUIRE(converter("1:1.0") == 1.0f);
        REQUIRE(converter("1:14") == 14.f);
        REQUIRE(converter("1:9.9") == 9.9f);
    }

    SECTION("float -> String")
    {
        mc::RatioCompTextConverter const converter {};
        REQUIRE(converter(1.0f) == "1:1.0");
        REQUIRE(converter(11.0f) == "1:11");
        REQUIRE(converter(9.f) == "1:9.0");
        REQUIRE(converter(30.1f) == "Limiter");
    }
}

TEST_CASE("core/text: RatioExpTextConverter", "[core][text]")
{
    SECTION("String -> float")
    {
        mc::RatioExpTextConverter const converter {};
        REQUIRE(converter("100:1") == 100.0f);
        REQUIRE(converter("1:1") == 1.0f);
        REQUIRE(converter("14:1") == 14.f);
        REQUIRE(converter("9.9:1") == 9.9f);
    }

    SECTION("float -> String")
    {
        mc::RatioExpTextConverter const converter {};
        REQUIRE(converter(1.0f) == "1.0:1");
        REQUIRE(converter(11.0f) == "11:1");
        REQUIRE(converter(9.f) == "9.0:1");
        REQUIRE(converter(21.f) == "Gate");
    }
}

TEST_CASE("core/text: InvertPhaseTextConverter", "[core][text]")
{
    SECTION("String -> float")
    {
        mc::InvertPhaseTextConverter const converter {};
        REQUIRE(converter("Normal") == 0.0f);
        REQUIRE(converter("Inverted") == 1.0f);
    }

    SECTION("float -> String")
    {
        mc::InvertPhaseTextConverter const converter {};
        REQUIRE(converter(0.0f) == "Normal");
        REQUIRE(converter(1.0f) == "Inverted");
    }
}

TEST_CASE("core/text: InvertPhaseBoolTextConverter", "[core][text]")
{
    SECTION("String -> bool")
    {
        mc::InvertPhaseBoolTextConverter const converter {};
        REQUIRE(converter(juce::String("Normal")) == false);
        REQUIRE(converter(juce::String("Inverted")) == true);
    }

    SECTION("bool -> String")
    {
        mc::InvertPhaseBoolTextConverter const converter {};
        REQUIRE(converter(false) == "Normal");
        REQUIRE(converter(true) == "Inverted");
    }
}