#pragma once

namespace mc {

struct HistogramSource {

    auto prepare(double sampleRate, std::uint32_t blockSize) -> void;
    auto process(juce::AudioBuffer<float> const& buffer) -> void;
    auto processSample(float sample, std::uint32_t sampleCountToAdvance) -> void;
    auto reset() -> void;

    MC_NODISCARD auto popSample() -> float;

private:
    double sampleRate_ { 44'100.0 };
    juce::AudioBuffer<float> summingBuffer_;
    Microseconds<double> timeSinceLastSample_ { 0 };
    std::atomic<float> lastValue_ { 0.0f };
};

} // namespace mc