#pragma once

namespace mc {

template <typename T>
[[nodiscard]] auto channel(juce::dsp::AudioBlock<T> const& block, size_t index) -> Span<T>;

template <typename T>
auto addStereoFrame(juce::dsp::AudioBlock<T> const& block, size_t index, StereoFrame<T> frame) -> void;

} // namespace mc

#include "audio_block.cpp" // NOLINT(bugprone-suspicious-include)
