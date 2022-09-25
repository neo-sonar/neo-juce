#pragma once

namespace mc {

/// \brief Text & float converter for active/bypass.
struct ActiveTextConverter {
    [[nodiscard]] auto operator()(float value, int maxStringLength = 0) const -> juce::String
    {
        juce::ignoreUnused(maxStringLength);
        return value > 0.5F ? juce::translate("active") : juce::translate("bypassed");
    }

    [[nodiscard]] auto operator()(juce::String const& text) const -> float
    {
        return static_cast<float>(text == juce::translate("active"));
    }
};
} // namespace mc
