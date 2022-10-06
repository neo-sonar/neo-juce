#pragma once

namespace mc {

/// \brief Text & float converter for filter quality.
struct QualityTextConverter {
    [[nodiscard]] auto operator()(float value, int maxStringLength = 0) const -> juce::String
    {

        juce::ignoreUnused(maxStringLength);
        return { value, 1 };
    }

    [[nodiscard]] auto operator()(juce::String const& text) const -> float { return text.getFloatValue(); }
};
} // namespace mc
