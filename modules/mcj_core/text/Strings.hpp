// SPDX-License-Identifier: BSL-1.0

#pragma once

namespace mc::strings {

[[nodiscard]] auto split(juce::String const& str, char delimiter) -> Vector<juce::String>;

template <typename T>
[[nodiscard]] auto toValue(juce::String const& str) -> T;

} // namespace mc::strings

#include "Strings.cpp" // NOLINT
