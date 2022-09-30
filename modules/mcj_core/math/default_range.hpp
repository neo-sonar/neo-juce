// SPDX-License-Identifier: BSL-1.0

#pragma once

namespace mc {

/// \brief Collection of preconfigured ranges.
template <typename T>
struct DefaultRange {
    static auto normalized() -> juce::NormalisableRange<T>;
    static auto gain() -> juce::NormalisableRange<T>;
    static auto frequency() -> juce::NormalisableRange<T>;
    static auto timeMilliseconds() -> juce::NormalisableRange<T>;
};

} // namespace mc

#include "default_range.cpp" // NOLINT(bugprone-suspicious-include)
