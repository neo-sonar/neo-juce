// SPDX-License-Identifier: BSL-1.0

#pragma once

namespace mc {

template <typename T>
[[nodiscard]] auto toString(T& obj) -> decltype(obj.toString())
{
    return obj.toString();
}

template <typename T>
[[nodiscard]] auto toString(T const& obj) -> decltype(obj.toString())
{
    return obj.toString();
}

} // namespace mc

template <>
struct fmt::formatter<juce::String> : formatter<string_view> {
    template <typename FormatContext>
    auto format(juce::String const& str, FormatContext& ctx) const
    {
        return fmt::format_to(ctx.out(), "{}", str.getCharPointer());
    }
};
