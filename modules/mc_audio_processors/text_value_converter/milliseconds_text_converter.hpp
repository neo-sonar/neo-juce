#pragma once

namespace mc {

/// \brief Text & float converter for durations based on seconds.
struct MillisecondsTextConverter {
    [[nodiscard]] auto operator()(float value, int maxStringLength = 0) const -> juce::String
    {
        juce::ignoreUnused(maxStringLength);
        return juce::String(value, 1) + " ms";
    }

    [[nodiscard]] auto operator()(juce::String const& text) const -> float
    {
        return text.dropLastCharacters(3).getFloatValue();
    }
};

} // namespace mc
