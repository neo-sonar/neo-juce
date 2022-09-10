#pragma once

namespace mc {
struct TrueFalseTextConverter {
    MC_NODISCARD auto operator()(float value, int maxStringLength = 0) const -> juce::String
    {
        juce::ignoreUnused(maxStringLength);
        return value > 0.5f ? "true" : "false";
    }

    MC_NODISCARD auto operator()(juce::String const& text) const -> float { return static_cast<float>(text == "true"); }
};
} // namespace mc
