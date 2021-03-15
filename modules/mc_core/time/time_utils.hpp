#ifndef MODERN_CIRCUITS_JUCE_MODULES_TIME_UTILS_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_TIME_UTILS_HPP

namespace mc
{
/**
 * @brief Returns the sample count converted to microseconds.
 */
template<typename ValueType>
[[nodiscard]] constexpr auto samplesToMicroseconds(int samples, double sampleRate) noexcept -> ValueType
{
    return static_cast<ValueType>((static_cast<double>(samples) / sampleRate) * 1'000'000.0);
}

/**
 * @brief Returns the sample count converted to milliseconds.
 */
template<typename ValueType>
[[nodiscard]] constexpr auto samplesToMilliseconds(int samples, double sampleRate) noexcept -> ValueType
{
    return samplesToMicroseconds<ValueType>(samples, sampleRate) / 1'000;
}

/**
 * @brief Returns the sample count converted to seconds.
 */
template<typename ValueType>
[[nodiscard]] constexpr auto samplesToSeconds(int samples, double sampleRate) noexcept -> ValueType
{
    return samplesToMilliseconds<ValueType>(samples, sampleRate) / 1'000;
}

/**
 * @brief Returns the given microseconds in samples.
 */
template<typename ValueType>
[[nodiscard]] constexpr auto microsecondsToSamples(double micros, double sampleRate) noexcept -> ValueType
{
    return static_cast<ValueType>((micros / 1'000'000) * sampleRate);
}

/**
 * @brief Returns the given milliseconds in samples.
 */
template<typename ValueType>
[[nodiscard]] constexpr auto millisecondsToSamples(double millis, double sampleRate) noexcept -> ValueType
{
    return static_cast<ValueType>((millis / 1'000) * sampleRate);
}

/**
 * @brief Returns the given seconds in samples.
 */
template<typename ValueType>
[[nodiscard]] constexpr auto secondsToSamples(double seconds, double sampleRate) noexcept -> ValueType
{
    return static_cast<ValueType>(seconds * sampleRate);
}

/**
 * @brief Returns given bar count in samples.
 */
[[nodiscard]] constexpr auto barsToSamples(double bars, double bpm, double sampleRate) noexcept -> double
{
    auto const barsPerMin    = bpm / 4;
    auto const samplesPerMin = sampleRate * 60.0;
    auto const samplesPerBar = samplesPerMin / barsPerMin;
    return samplesPerBar * bars;
}

}  // namespace mc
template<>
struct juce::VariantConverter<juce::Time>
{
    [[nodiscard]] static auto fromVar(juce::var const& v) -> juce::Time
    {
        return juce::Time::fromISO8601(v.toString());
    }

    [[nodiscard]] static auto toVar(juce::Time const& t) -> juce::var
    {
        auto str = t.toISO8601(true);
        return str;
    }
};

#endif  // MODERN_CIRCUITS_JUCE_MODULES_TIME_UTILS_HPP
