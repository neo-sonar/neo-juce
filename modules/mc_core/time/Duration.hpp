#pragma once

namespace mc {

/// \brief Duration type based on double.
template <typename R>
using Duration = std::chrono::duration<double, R>;

/// \brief Duration in microseconds.
using Microseconds = Duration<std::micro>;

/// \brief Duration in milliseconds.
using Milliseconds = Duration<std::milli>;

/// \brief Duration in seconds.
using Seconds = Duration<std::ratio<1>>;

/// \brief Converts a duration to milliseconds.
template <typename R>
MC_NODISCARD constexpr auto toMilliseconds(Duration<R> const& duration) noexcept -> Seconds
{
    return std::chrono::duration_cast<Milliseconds>(duration);
}

/// \brief Converts a duration to seconds.
template <typename R>
MC_NODISCARD constexpr auto toSeconds(Duration<R> const& duration) noexcept -> Seconds
{
    return std::chrono::duration_cast<Seconds>(duration);
}

} // namespace mc

/// \internal
template <typename T, typename R>
struct juce::VariantConverter<std::chrono::duration<T, R>> {
    MC_NODISCARD static auto fromVar(juce::var const& v) -> std::chrono::duration<T, R>
    {
        if constexpr (std::is_floating_point_v<T>) {
            return std::chrono::duration<T, R> { static_cast<T>(v) };
        }
        return std::chrono::duration<T, R> { static_cast<T>(static_cast<juce::int64>(v)) };
    }

    MC_NODISCARD static auto toVar(std::chrono::duration<T, R> const& d) -> juce::var
    {
        if constexpr (std::is_floating_point_v<T>) {
            return juce::var { d.count() };
        }
        return juce::var { static_cast<juce::int64>(d.count()) };
    }
};
