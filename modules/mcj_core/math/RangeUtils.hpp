// SPDX-License-Identifier: BSL-1.0

#pragma once

namespace mc {

/// \brief Collection of preconfigured ranges.
struct RangeUtils {

    /// \brief Returns a normalized range.
    static auto defaultNormalizedRange() noexcept -> juce::NormalisableRange<float>;

    /// \brief Returns a range for gain parameters.
    static auto defaultGainRange() noexcept -> juce::NormalisableRange<float>;

    /// \brief Returns a range for full range frequency parameters.
    static auto defaultFrequencyRange() noexcept -> juce::NormalisableRange<float>;

    static auto defaultTimeRange() noexcept -> juce::NormalisableRange<float>;
};

} // namespace mc
