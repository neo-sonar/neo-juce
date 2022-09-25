#include <mcj_audio_processors/mcj_audio_processors.hpp>

#include <catch2/catch_approx.hpp>
#include <catch2/catch_template_test_macros.hpp>

TEST_CASE("audio_processors/parameter: ActiveTextConverter", "[audio_processors]")
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

TEST_CASE("audio_processors/parameter: FrequencyTextConverter", "[audio_processors]")
{
    SECTION("String -> float")
    {
        mc::FrequencyTextConverter const converter {};
        REQUIRE(converter("10 Hz") == 10.0F);
        REQUIRE(converter("10.00 kHz") == 10000.0F);
    }

    SECTION("float -> String")
    {
        mc::FrequencyTextConverter const converter {};
        REQUIRE(converter(10.0F) == "10 Hz");
        REQUIRE(converter(10000.0F) == "10.00 kHz");
    }
}

TEST_CASE("audio_processors/parameter: QualityTextConverter", "[audio_processors]")
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

TEST_CASE("audio_processors/parameter: GainTextConverter", "[audio_processors]")
{
    SECTION("String -> float")
    {
        mc::GainTextConverter const converter {};
        REQUIRE(converter("0.0 db") == Catch::Approx(1.0F));
    }
    SECTION("String -> float")
    {
        mc::GainTextConverter const converter {};
        REQUIRE(converter("1.0 db") == Catch::Approx(1.12202F));
    }
    SECTION("String -> float")
    {
        mc::GainTextConverter const converter {};
        REQUIRE(converter("6.0 db") == Catch::Approx(1.99526F));
    }
}

TEST_CASE("audio_processors/parameter: PercentTextConverter", "[audio_processors]")
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

TEST_CASE("audio_processors/parameter: TimeSecondsTextConverter", "[audio_processors]")
{
    SECTION("String -> float")
    {
        mc::TimeSecondsTextConverter const converter {};
        REQUIRE(converter("100.0 s") == 100.0F);
        REQUIRE(converter("0.00 s") == 0.0F);
        REQUIRE(converter("14.30 s") == 14.3F);
    }

    SECTION("float -> String")
    {
        mc::TimeSecondsTextConverter const converter {};
        REQUIRE(converter(0.0F) == "0.00 s");
        REQUIRE(converter(1.0F) == "1.00 s");
        REQUIRE(converter(14.3F) == "14.30 s");
    }
}

TEST_CASE("audio_processors/parameter: TimeMillisecondsTextConverter", "[audio_processors]")
{
    SECTION("String -> float")
    {
        mc::TimeMillisecondsTextConverter const converter {};
        REQUIRE(converter("100.0 ms") == 100.0F);
        REQUIRE(converter("0.0 ms") == 0.0F);
        REQUIRE(converter("14.3 ms") == 14.3F);
    }

    SECTION("float -> String")
    {
        mc::TimeMillisecondsTextConverter const converter {};
        REQUIRE(converter(0.0F) == "0.0 ms");
        REQUIRE(converter(1.0F) == "1.0 ms");
        REQUIRE(converter(14.3F) == "14.3 ms");
    }
}

TEST_CASE("audio_processors/parameter: RatioCompTextConverter", "[audio_processors]")
{
    SECTION("String -> float")
    {
        mc::RatioCompTextConverter const converter {};
        REQUIRE(converter("1:100") == 100.0F);
        REQUIRE(converter("1:1.0") == 1.0F);
        REQUIRE(converter("1:14") == 14.F);
        REQUIRE(converter("1:9.9") == 9.9F);
    }

    SECTION("float -> String")
    {
        mc::RatioCompTextConverter const converter {};
        REQUIRE(converter(1.0F) == "1:1.0");
        REQUIRE(converter(11.0F) == "1:11");
        REQUIRE(converter(9.F) == "1:9.0");
        REQUIRE(converter(30.1F) == "Limiter");
    }
}

TEST_CASE("audio_processors/parameter: RatioExpTextConverter", "[audio_processors]")
{
    SECTION("String -> float")
    {
        mc::RatioExpTextConverter const converter {};
        REQUIRE(converter("100:1") == 100.0F);
        REQUIRE(converter("1:1") == 1.0F);
        REQUIRE(converter("14:1") == 14.F);
        REQUIRE(converter("9.9:1") == 9.9F);
    }

    SECTION("float -> String")
    {
        mc::RatioExpTextConverter const converter {};
        REQUIRE(converter(1.0F) == "1.0:1");
        REQUIRE(converter(11.0F) == "11:1");
        REQUIRE(converter(9.F) == "9.0:1");
        REQUIRE(converter(21.F) == "Gate");
    }
}

TEST_CASE("audio_processors/parameter: InvertPhaseTextConverter", "[audio_processors]")
{
    SECTION("String -> float")
    {
        mc::InvertPhaseTextConverter const converter {};
        REQUIRE(converter("Normal") == 0.0F);
        REQUIRE(converter("Inverted") == 1.0F);
    }

    SECTION("float -> String")
    {
        mc::InvertPhaseTextConverter const converter {};
        REQUIRE(converter(0.0F) == "Normal");
        REQUIRE(converter(1.0F) == "Inverted");
    }
}

TEST_CASE("audio_processors/parameter: InvertPhaseBoolTextConverter", "[audio_processors]")
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
