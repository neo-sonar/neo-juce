// SPDX-License-Identifier: BSL-1.0

#pragma once

namespace neo {

template <typename T>
[[nodiscard]] auto toVector(juce::AudioBuffer<T> const& buffer) -> std::vector<T>;

template <typename T>
[[nodiscard]] auto channel(juce::AudioBuffer<T>& buffer, size_t index) -> std::span<T>;

template <typename T>
[[nodiscard]] auto channel(juce::AudioBuffer<T> const& buffer, size_t index) -> std::span<T const>;

} // namespace neo

#include "audio_buffer.cpp" // NOLINT(bugprone-suspicious-include)
