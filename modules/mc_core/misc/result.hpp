// SPDX-License-Identifier: BSL-1.0

#pragma once

namespace mc {

template <typename... T>
[[nodiscard]] auto fail(::fmt::format_string<T...> fmt, T&&... args) -> juce::Result
{
    return juce::Result::fail(jformat(fmt, std::forward<T>(args)...));
}

} // namespace mc
