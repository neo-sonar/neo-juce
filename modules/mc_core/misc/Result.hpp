#pragma once

namespace mc {

template <typename... T>
MC_NODISCARD auto fail(::fmt::format_string<T...> fmt, T&&... args) -> juce::Result
{
    return juce::Result::fail(jformat(fmt, std::forward<T>(args)...));
}

} // namespace mc
