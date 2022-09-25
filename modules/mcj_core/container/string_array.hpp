// SPDX-License-Identifier: BSL-1.0

#pragma once

template <>
struct fmt::formatter<juce::StringArray> : formatter<string_view> {
    template <typename FormatContext>
    auto format(juce::StringArray const& array, FormatContext& ctx) const
    {
        return fmt::format_to(ctx.out(), "{}", fmt::join(array, ", "));
    }
};
