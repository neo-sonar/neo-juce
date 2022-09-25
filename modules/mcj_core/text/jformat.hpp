// SPDX-License-Identifier: BSL-1.0

#pragma once

namespace mc {

template <typename... T>
auto jformat(::fmt::format_string<T...> fmt, T&&... args) -> juce::String
{
    return juce::String { ::fmt::format(fmt, std::forward<T>(args)...) };
}

} // namespace mc
