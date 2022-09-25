#pragma once

namespace mc {

/// \brief Text & float converter for gain.
struct GainTextConverter {
    [[nodiscard]] auto operator()(float value, int maxStringLength = 0) const -> juce::String
    {
        juce::ignoreUnused(maxStringLength);
        return juce::String(juce::Decibels::gainToDecibels(value), 1) + " dB";
    }

    [[nodiscard]] auto operator()(juce::String const& text) const -> float
    {
        return juce::Decibels::decibelsToGain(text.dropLastCharacters(3).getFloatValue());
    }
};

} // namespace mc
