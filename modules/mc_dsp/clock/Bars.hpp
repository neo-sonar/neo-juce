#pragma once

namespace mc {

/// \brief Converts the duration to a sample count based on the sample-rate.
/// \see Duration
template <typename T, typename R>
auto toSampleCount(Duration<T, R> const& duration, double sampleRate) noexcept -> double
{
    return toSeconds(duration).count() * sampleRate;
}

/// \brief Returns given bar count in samples.
MC_NODISCARD constexpr auto barsToSamples(double bars, double bpm, double sampleRate) noexcept -> double
{
    auto const barsPerMin    = bpm / 4;
    auto const samplesPerMin = sampleRate * 60.0;
    auto const samplesPerBar = samplesPerMin / barsPerMin;
    return samplesPerBar * bars;
}

MC_NODISCARD constexpr auto barsToMilliseconds(double bpm, double num, double denom) noexcept -> Milliseconds<double>
{
    return Milliseconds<double> { (60'000.0 / bpm) * 4.0 * (num / denom) };
}

MC_NODISCARD constexpr auto barsToSeconds(double bpm, double num, double denom) noexcept -> Seconds<double>
{
    return toSeconds(barsToMilliseconds(bpm, num, denom));
}

/// \brief Returns the sample count converted to microseconds.
MC_NODISCARD constexpr auto samplesToMicroseconds(int samples, double sampleRate) noexcept -> Microseconds<double>
{
    return Microseconds<double> { (static_cast<double>(samples) / sampleRate) * 1'000'000.0 };
}

/// \brief Returns the sample count converted to milliseconds.
MC_NODISCARD constexpr auto samplesToMilliseconds(int samples, double sampleRate) noexcept -> Milliseconds<double>
{
    return toMilliseconds(samplesToMicroseconds(samples, sampleRate));
}

/// \brief Returns the sample count converted to seconds.
MC_NODISCARD constexpr auto samplesToSeconds(int samples, double sampleRate) noexcept -> Seconds<double>
{
    return toSeconds(samplesToMicroseconds(samples, sampleRate));
}

template <typename T>
MC_NODISCARD constexpr auto bpmToHertz(T bpm) noexcept -> T
{
    return bpm / T { 60 };
}
}