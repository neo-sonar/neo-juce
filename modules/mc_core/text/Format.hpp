#pragma once

namespace mc {

using ::fmt::format;

template <typename... T>
auto jformat(::fmt::format_string<T...> fmt, T&&... args) -> juce::String
{
    return juce::String { ::fmt::format(fmt, std::forward<T>(args)...) };
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

template <>
struct fmt::formatter<juce::File> : formatter<string_view> {
    template <typename FormatContext>
    auto format(juce::File const& file, FormatContext& ctx) const
    {
        return fmt::format_to(ctx.out(), "{}", file.getFullPathName());
    }
};

template <>
struct fmt::formatter<juce::StringArray> : formatter<string_view> {
    template <typename FormatContext>
    auto format(juce::StringArray const& array, FormatContext& ctx) const
    {
        return fmt::format_to(ctx.out(), "{}", fmt::join(array, ", "));
    }
};
