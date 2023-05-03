#pragma once

namespace mc {

/// \brief Text & float converter for frequency.
struct FrequencyTextConverter {
    [[nodiscard]] auto operator()(float value, int maxStringLength = 0) const -> juce::String
    {
        juce::ignoreUnused(maxStringLength);
        return (value < 1000) ? juce::String(value, 2) + " Hz" : juce::String(value / 1000.0, 2) + " kHz";
    }

    [[nodiscard]] auto operator()(juce::String const& text) const -> float
    {
        return text.endsWith(" kHz") ? static_cast<float>(text.dropLastCharacters(4).getFloatValue() * 1000.0)
                                     : static_cast<float>(text.dropLastCharacters(3).getFloatValue());
    }
};

} // namespace mc
