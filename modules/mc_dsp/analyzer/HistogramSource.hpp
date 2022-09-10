#pragma once

namespace mc {

struct HistogramSource {

    auto prepare(double sampleRate, std::uint32_t blockSize) -> void;
    auto process(juce::AudioBuffer<float> const& buffer) -> void;
    auto processSample(float sample, std::uint32_t sampleCountToAdvance) -> void;
    auto reset() -> void;

    MC_NODISCARD auto popSample() -> float;

private:
    double _sampleRate { 44'100.0 };
    juce::AudioBuffer<float> _summingBuffer;
    Microseconds<double> _timeSinceLastSample { 0 };
    Atomic<float> _lastValue { 0.0F };
};

} // namespace mc
