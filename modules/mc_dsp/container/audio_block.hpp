#pragma once

namespace mc {

template <typename T>
[[nodiscard]] auto channel(juce::dsp::AudioBlock<T> const& block, size_t index) -> Span<T>;

template <typename T>
auto addStereoFrame(juce::dsp::AudioBlock<T> const& block, size_t index, StereoFrame<T> frame) -> void;

template <typename T>
auto rmsLevel(juce::dsp::AudioBlock<T> const& block) -> T;

} // namespace mc

#include "audio_block.cpp" // NOLINT(bugprone-suspicious-include)
