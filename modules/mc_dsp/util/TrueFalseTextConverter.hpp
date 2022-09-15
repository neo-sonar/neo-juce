#pragma once

namespace mc {
struct TrueFalseTextConverter {
    [[nodiscard]] auto operator()(float value, int maxStringLength = 0) const -> juce::String
    {
        juce::ignoreUnused(maxStringLength);
        return value > 0.5F ? "true" : "false";
    }

    [[nodiscard]] auto operator()(juce::String const& text) const -> float
    {
        return static_cast<float>(text == "true");
    }
};
} // namespace mc
