#pragma once

template <>
struct juce::VariantConverter<juce::Colour> {
    MC_NODISCARD static auto fromVar(juce::var const& v) -> juce::Colour;
    MC_NODISCARD static auto toVar(juce::Colour const& c) -> juce::var;
};
