#include "mc_graphics/mc_graphics.hpp"

#include <catch2/catch_template_test_macros.hpp>

TEST_CASE("graphics/images: VariantConverter<juce::Image>", "")
{
    SECTION("rgb cleared")
    {
        auto const original = juce::Image { juce::Image::RGB, 2, 2, true };
        auto const value    = juce::VariantConverter<juce::Image>::toVar(original);
        auto const result   = juce::VariantConverter<juce::Image>::fromVar(value);
        CHECK(original.isValid() == result.isValid());
        CHECK(original.getBounds() == result.getBounds());
        CHECK(original.getFormat() == result.getFormat());
    }
}
