#pragma once

namespace neo {

template <typename T>
[[nodiscard]] auto channel(juce::dsp::AudioBlock<T> const& block, size_t index) -> std::span<T>;

template <typename T>
auto rmsLevel(juce::dsp::AudioBlock<T> const& block) -> T;

} // namespace neo

#include "audio_block.cpp" // NOLINT(bugprone-suspicious-include)
