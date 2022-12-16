#pragma once

namespace mc {

template <typename T>
struct BufferWithSampleRate {
    juce::AudioBuffer<T> buffer;
    double sampleRate;
};


/// \relates BufferWithSampleRate
[[nodiscard]] auto toVector(BufferWithSampleRate<float> const& buffer) -> Vector<float>;

/// \relates BufferWithSampleRate
[[nodiscard]] auto toVector(BufferWithSampleRate<double> const& buffer) -> Vector<double>;

} // namespace mc
