#pragma once

template <>
struct juce::VariantConverter<juce::Image> {
    MC_NODISCARD static auto fromVar(juce::var const& v) -> juce::Image;
    MC_NODISCARD static auto toVar(juce::Image const& i) -> juce::var;
};
