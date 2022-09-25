// SPDX-License-Identifier: BSL-1.0

#pragma once

namespace mc {

template <typename T>
[[nodiscard]] auto toVector(juce::AudioBuffer<T> const& buffer) -> Vector<T>;

template <typename T>
[[nodiscard]] auto channel(juce::AudioBuffer<T>& buffer, size_t index) -> Span<T>;

template <typename T>
[[nodiscard]] auto channel(juce::AudioBuffer<T> const& buffer, size_t index) -> Span<T const>;

} // namespace mc

#include "audio_buffer.cpp"
