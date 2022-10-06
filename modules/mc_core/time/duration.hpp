// SPDX-License-Identifier: BSL-1.0

#pragma once

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
