// SPDX-License-Identifier: BSL-1.0

#pragma once


namespace mc {

/// \brief Duration.
template <typename T, typename R>
using Duration = std::chrono::duration<T, R>;

/// \brief Duration in microseconds.
template <typename T>
using Microseconds = Duration<T, std::micro>;

/// \brief Duration in milliseconds.
template <typename T>
using Milliseconds = Duration<T, std::milli>;

/// \brief Duration in seconds.
template <typename T>
using Seconds = Duration<T, std::ratio<1>>;

/// \brief Converts a duration to milliseconds.
template <typename T, typename R>
[[nodiscard]] constexpr auto toMilliseconds(Duration<T, R> const& d) noexcept
{
    return std::chrono::duration_cast<Milliseconds<T>>(d);
}

/// \brief Converts a duration to seconds.
template <typename T, typename R>
[[nodiscard]] constexpr auto toSeconds(Duration<T, R> const& d) noexcept
{
    return std::chrono::duration_cast<Seconds<T>>(d);
}

} // namespace mc

/// \internal
template <typename T, typename R>
struct juce::VariantConverter<std::chrono::duration<T, R>> {
    [[nodiscard]] static auto fromVar(juce::var const& v) -> std::chrono::duration<T, R>
    {
        if constexpr (std::is_floating_point_v<T>) {
            return std::chrono::duration<T, R> { static_cast<T>(v) };
        } else {
            return std::chrono::duration<T, R> { static_cast<T>(static_cast<juce::int64>(v)) };
        }
    }

    [[nodiscard]] static auto toVar(std::chrono::duration<T, R> const& d) -> juce::var
    {
        if constexpr (std::is_floating_point_v<T>) {
            return juce::var { d.count() };
        } else {
            return juce::var { static_cast<juce::int64>(d.count()) };
        }
    }
};
