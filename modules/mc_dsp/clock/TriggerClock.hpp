#pragma once

namespace mc {

struct TriggerClock {
    auto reset(std::int64_t sampleCount = 0) -> void;
    auto setTickLength(Milliseconds milli) -> void;
    auto setSampleRate(double sampleRate) -> void;

    [[nodiscard]] auto advance(std::int64_t numSamples) -> bool;

private:
    std::int64_t sampleCount_ { 0 };
    std::uint64_t tickLength_ { 0 };
    double sampleRate_ { 0 };
};

}