#include "mc_core/mc_core.hpp"

#include "catch2/catch_test_macros.hpp"

TEST_CASE("mc_core: VariantConverter<juce::Image>", "[core][image]")
{
    SECTION("rgb cleared")
    {
        auto const original = juce::Image {juce::Image::RGB, 2, 2, true};
        auto const value    = juce::VariantConverter<juce::Image>::toVar(original);
        auto const result   = juce::VariantConverter<juce::Image>::fromVar(value);
        CHECK(original.isValid() == result.isValid());
        CHECK(original.getBounds() == result.getBounds());
        CHECK(original.getFormat() == result.getFormat());
    }
}