#pragma once

namespace neo {

struct HistogramSource {

    auto prepare(double sampleRate, std::uint32_t blockSize) -> void;
    auto process(juce::AudioBuffer<float> const& buffer) -> void;
    auto processSample(float sample, std::uint32_t sampleCountToAdvance) -> void;
    auto reset() -> void;

    [[nodiscard]] auto popSample() -> float;

private:
    double _sampleRate { 44'100.0 };
    juce::AudioBuffer<float> _summingBuffer;
    std::chrono::duration<double, std::micro> _timeSinceLastSample { 0 };
    std::atomic<float> _lastValue { 0.0F };
};

} // namespace neo
