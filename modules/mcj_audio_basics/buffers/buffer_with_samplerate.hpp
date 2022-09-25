#pragma once

namespace mc {

template <typename T>
struct BufferWithSampleRate {
    juce::AudioBuffer<T> buffer;
    double sampleRate;
};

[[nodiscard]] auto toVector(BufferWithSampleRate<float> const& buffer) -> Vector<float>;
[[nodiscard]] auto toVector(BufferWithSampleRate<double> const& buffer) -> Vector<double>;

} // namespace mc
