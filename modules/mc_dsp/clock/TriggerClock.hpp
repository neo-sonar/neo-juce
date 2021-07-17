#pragma once

namespace mc {

template <typename R>
auto toSampleCount(Duration<R> const& duration, double sampleRate) noexcept -> double
{
    return toSeconds(duration).count() * sampleRate;
}

template <typename T>
[[nodiscard]] constexpr auto bpmToHertz(T bpm) noexcept -> T
{
    return bpm / T { 60 };
}

[[nodiscard]] constexpr auto barsToMilliseconds(double bpm, double num, double denom) noexcept -> Milliseconds
{
    return Milliseconds { (60'000.0 / bpm) * 4.0 * (num / denom) };
}

[[nodiscard]] constexpr auto barsToSeconds(double bpm, double num, double denom) noexcept -> Seconds
{
    return toSeconds(barsToMilliseconds(bpm, num, denom));
}

/// \brief Returns the sample count converted to microseconds.
template <typename ValueType>
[[nodiscard]] constexpr auto samplesToMicroseconds(int samples, double sampleRate) noexcept -> ValueType
{
    return static_cast<ValueType>((static_cast<double>(samples) / sampleRate) * 1'000'000.0);
}

/// \brief Returns the sample count converted to milliseconds.
template <typename ValueType>
[[nodiscard]] constexpr auto samplesToMilliseconds(int samples, double sampleRate) noexcept -> ValueType
{
    return samplesToMicroseconds<ValueType>(samples, sampleRate) / 1'000;
}

/// \brief Returns the sample count converted to seconds.
template <typename ValueType>
[[nodiscard]] constexpr auto samplesToSeconds(int samples, double sampleRate) noexcept -> ValueType
{
    return samplesToMilliseconds<ValueType>(samples, sampleRate) / 1'000;
}

/// \brief Returns the given microseconds in samples.
template <typename ValueType>
[[nodiscard]] constexpr auto microsecondsToSamples(double micros, double sampleRate) noexcept -> ValueType
{
    return static_cast<ValueType>((micros / 1'000'000) * sampleRate);
}

/// \brief Returns the given milliseconds in samples.
template <typename ValueType>
[[nodiscard]] constexpr auto millisecondsToSamples(double millis, double sampleRate) noexcept -> ValueType
{
    return static_cast<ValueType>((millis / 1'000) * sampleRate);
}

/// \brief Returns the given seconds in samples.
template <typename ValueType>
[[nodiscard]] constexpr auto secondsToSamples(double seconds, double sampleRate) noexcept -> ValueType
{
    return static_cast<ValueType>(seconds * sampleRate);
}

/// \brief Returns given bar count in samples.
[[nodiscard]] constexpr auto barsToSamples(double bars, double bpm, double sampleRate) noexcept -> double
{
    auto const barsPerMin    = bpm / 4;
    auto const samplesPerMin = sampleRate * 60.0;
    auto const samplesPerBar = samplesPerMin / barsPerMin;
    return samplesPerBar * bars;
}

struct TriggerClock {
    auto advance(std::uint32_t numSamples) -> bool
    {
        auto ticked { false };
        for (std::uint32_t i { 0 }; i < numSamples; ++i) {
            if (sampleCount_++ % tickLength_ == 0) {
                ticked = true;
            }
        }
        return ticked;
    }
    auto reset() -> void { sampleCount_ = 0; }
    auto setTickLength(Milliseconds milli) -> void
    {
        tickLength_ = static_cast<std::uint32_t>(toSampleCount(milli, sampleRate_));
    }
    auto setSampleRate(double sampleRate) -> void { sampleRate_ = sampleRate; }

private:
    std::uint32_t sampleCount_ { 0 };
    std::uint32_t tickLength_ { 0 };
    double sampleRate_ { 0 };
};
}