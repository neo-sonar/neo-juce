#pragma once

namespace mc {

/// \brief Converts the duration to a sample count based on the sample-rate.
template <typename R>
auto toSampleCount(Duration<R> const& duration, double sampleRate) noexcept -> double
{
    return toSeconds(duration).count() * sampleRate;
}

/// \brief Returns given bar count in samples.
[[nodiscard]] constexpr auto barsToSamples(double bars, double bpm, double sampleRate) noexcept -> double
{
    auto const barsPerMin    = bpm / 4;
    auto const samplesPerMin = sampleRate * 60.0;
    auto const samplesPerBar = samplesPerMin / barsPerMin;
    return samplesPerBar * bars;
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
[[nodiscard]] constexpr auto samplesToMicroseconds(int samples, double sampleRate) noexcept -> Microseconds
{
    return Microseconds { (static_cast<double>(samples) / sampleRate) * 1'000'000.0 };
}

/// \brief Returns the sample count converted to milliseconds.
[[nodiscard]] constexpr auto samplesToMilliseconds(int samples, double sampleRate) noexcept -> Milliseconds
{
    return toMilliseconds(samplesToMicroseconds(samples, sampleRate));
}

/// \brief Returns the sample count converted to seconds.
[[nodiscard]] constexpr auto samplesToSeconds(int samples, double sampleRate) noexcept -> Seconds
{
    return toSeconds(samplesToMicroseconds(samples, sampleRate));
}

template <typename T>
[[nodiscard]] constexpr auto bpmToHertz(T bpm) noexcept -> T
{
    return bpm / T { 60 };
}
}