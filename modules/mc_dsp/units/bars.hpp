#pragma once

namespace mc {

/// \brief Returns given bar count in samples.
[[nodiscard]] constexpr auto barsToSamples(double bars, double bpm, double sampleRate) noexcept -> double
{
    auto const barsPerMin    = bpm / 4;
    auto const samplesPerMin = sampleRate * 60.0;
    auto const samplesPerBar = samplesPerMin / barsPerMin;
    return samplesPerBar * bars;
}

[[nodiscard]] constexpr auto barsToMilliseconds(double bpm, double num, double denom) noexcept -> Milliseconds<double>
{
    return Milliseconds<double> { (60'000.0 / bpm) * 4.0 * (num / denom) };
}

[[nodiscard]] constexpr auto barsToSeconds(double bpm, double num, double denom) noexcept -> Seconds<double>
{
    return toSeconds(barsToMilliseconds(bpm, num, denom));
}

} // namespace mc
