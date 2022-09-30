#include <mcj_graphics/mcj_graphics.hpp>

#include <catch2/catch_template_test_macros.hpp>

TEST_CASE("graphics/images: VariantConverter<juce::Image>", "[graphics]")
{
    SECTION("rgb cleared")
    {
        auto const original = juce::Image { juce::Image::RGB, 2, 2, true };
        auto const value    = juce::VariantConverter<juce::Image>::toVar(original);
        auto const result   = juce::VariantConverter<juce::Image>::fromVar(value);
        REQUIRE(original.isValid() == result.isValid());
        REQUIRE(original.getBounds() == result.getBounds());
        REQUIRE(original.getFormat() == result.getFormat());
    }

    SECTION("red_256x256.jpg")
    {
        auto const path     = juce::File::getCurrentWorkingDirectory().getChildFile("test_data/img/red_256x256.jpg");
        auto const original = juce::ImageCache::getFromFile(path);
        REQUIRE(original.getBounds().getWidth() == 256);
        REQUIRE(original.getBounds().getHeight() == 256);

        auto const value  = juce::VariantConverter<juce::Image>::toVar(original);
        auto const result = juce::VariantConverter<juce::Image>::fromVar(value);
        REQUIRE(original.isValid() == result.isValid());
        REQUIRE(original.getBounds() == result.getBounds());
        REQUIRE(original.getFormat() == result.getFormat());
    }
}
