#pragma once

namespace mc {

/// \brief Text & float converter for phase invert.
struct InvertPhaseTextConverter {
    [[nodiscard]] auto operator()(float value, int maxStringLength = 0) const -> juce::String
    {
        juce::ignoreUnused(maxStringLength);
        return value < 0.5 ? "Normal" : "Inverted";
    }

    [[nodiscard]] auto operator()(juce::String const& text) const -> float { return text == "Normal" ? 0.0F : 1.0F; }
};
} // namespace mc
