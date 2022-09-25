#pragma once

namespace mc {

/// \brief Text & float converter for durations based on seconds.
struct SecondsTextConverter {
    [[nodiscard]] auto operator()(float value, int maxStringLength = 0) const -> juce::String
    {
        juce::ignoreUnused(maxStringLength);
        return juce::String(value, 2) + " s";
    }

    [[nodiscard]] auto operator()(juce::String const& text) const -> float
    {
        return text.dropLastCharacters(2).getFloatValue();
    }
};
} // namespace mc
