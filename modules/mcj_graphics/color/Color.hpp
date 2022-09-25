#pragma once

template <>
struct juce::VariantConverter<juce::Colour> {
    [[nodiscard]] static auto fromVar(juce::var const& v) -> juce::Colour;
    [[nodiscard]] static auto toVar(juce::Colour const& c) -> juce::var;
};
