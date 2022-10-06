#pragma once

namespace mc {

struct RatioOrLimiterTextConverter {
    [[nodiscard]] auto operator()(float value, int maxStringLength = 0) const -> juce::String
    {
        juce::ignoreUnused(maxStringLength);

        if (value > 30.F) { return "Limiter"; }
        if (value < 10.F) { return "1:" + juce::String(value, 1); }
        return "1:" + juce::String(static_cast<int>(value));
    }

    [[nodiscard]] auto operator()(juce::String const& text) const -> float { return text.substring(2).getFloatValue(); }
};

} // namespace mc
