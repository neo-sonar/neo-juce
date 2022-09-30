#pragma once

namespace mc {

/// \brief Converts the duration to a sample count based on the sample-rate.
/// \see Duration
template <typename T, typename R>
auto toSampleCount(Duration<T, R> const& duration, double sampleRate) noexcept -> double
{
    return toSeconds(duration).count() * sampleRate;
}

/// \brief Returns the sample count converted to microseconds.
[[nodiscard]] constexpr auto samplesToMicroseconds(int samples, double sampleRate) noexcept -> Microseconds<double>
{
    return Microseconds<double> { (static_cast<double>(samples) / sampleRate) * 1'000'000.0 };
}

/// \brief Returns the sample count converted to milliseconds.
[[nodiscard]] constexpr auto samplesToMilliseconds(int samples, double sampleRate) noexcept -> Milliseconds<double>
{
    return toMilliseconds(samplesToMicroseconds(samples, sampleRate));
}

/// \brief Returns the sample count converted to seconds.
[[nodiscard]] constexpr auto samplesToSeconds(int samples, double sampleRate) noexcept -> Seconds<double>
{
    return toSeconds(samplesToMicroseconds(samples, sampleRate));
}

} // namespace mc
