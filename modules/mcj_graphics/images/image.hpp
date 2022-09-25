#pragma once

template <>
struct juce::VariantConverter<juce::Image> {
    [[nodiscard]] static auto fromVar(juce::var const& v) -> juce::Image;
    [[nodiscard]] static auto toVar(juce::Image const& i) -> juce::var;
};
