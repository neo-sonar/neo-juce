#pragma once

namespace mc {

/// \brief Text & float converter for percentages.
struct PercentTextConverter {
    [[nodiscard]] auto operator()(float value, int maxStringLength = 0) const -> juce::String
    {
        juce::ignoreUnused(maxStringLength);
        return juce::String(value * 100.0F, 1) + " %";
    }

    [[nodiscard]] auto operator()(juce::String const& text) const -> float
    {
        return text.dropLastCharacters(2).getFloatValue() / 100.0F;
    }
};

} // namespace mc
