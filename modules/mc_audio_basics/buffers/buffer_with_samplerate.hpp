#pragma once

namespace mc {

template <typename T>
struct BufferWithSampleRate {
    juce::AudioBuffer<T> buffer;
    double sampleRate;
};

/// \relates BufferWithSampleRate
[[nodiscard]] auto toVector(BufferWithSampleRate<float> const& buffer) -> std::vector<float>;

/// \relates BufferWithSampleRate
[[nodiscard]] auto toVector(BufferWithSampleRate<double> const& buffer) -> std::vector<double>;

} // namespace mc
