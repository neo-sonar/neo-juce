#pragma once

namespace neo {

struct TriggerClock {
    auto reset(std::int64_t sampleCount = 0) -> void;
    auto setTickLength(Milliseconds<double> milli) -> void;
    auto setSampleRate(double sampleRate) -> void;

    [[nodiscard]] auto advance(std::int64_t numSamples) -> bool;

private:
    std::int64_t _sampleCount { 0 };
    std::uint64_t _tickLength { 0 };
    double _sampleRate { 0 };
};

} // namespace neo
