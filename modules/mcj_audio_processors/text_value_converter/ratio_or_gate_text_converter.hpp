#pragma once

namespace mc {

struct RatioOrGateTextConverter {
    [[nodiscard]] auto operator()(float value, int maxStringLength = 0) const -> juce::String
    {
        juce::ignoreUnused(maxStringLength);

        if (value == 21.F) { return "Gate"; }
        if (value < 10.F) { return juce::String(value, 1) + ":1"; }
        return juce::String(static_cast<int>(value)) + ":1";
    }

    [[nodiscard]] auto operator()(juce::String const& text) const -> float
    {
        return text.dropLastCharacters(2).getFloatValue();
    }
};

} // namespace mc
