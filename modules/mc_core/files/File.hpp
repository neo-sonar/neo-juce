#pragma once

template <>
struct juce::VariantConverter<juce::File> {
    MC_NODISCARD static auto fromVar(juce::var const& v) -> juce::File { return juce::File { v.toString() }; }
    MC_NODISCARD static auto toVar(juce::File const& file) -> juce::var { return file.getFullPathName(); }
};
