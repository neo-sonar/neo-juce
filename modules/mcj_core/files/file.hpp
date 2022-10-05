// SPDX-License-Identifier: BSL-1.0

#pragma once

namespace mc {
[[nodiscard]] inline auto makeFile(juce::StringRef relativeOrAbsolutePath) -> juce::File
{
    if (juce::File::isAbsolutePath(relativeOrAbsolutePath)) { return juce::File { relativeOrAbsolutePath }; }
    return juce::File::getCurrentWorkingDirectory().getChildFile(relativeOrAbsolutePath);
}
} // namespace mc

template <>
struct juce::VariantConverter<juce::File> {
    [[nodiscard]] static auto fromVar(juce::var const& v) -> juce::File { return juce::File { v.toString() }; }
    [[nodiscard]] static auto toVar(juce::File const& file) -> juce::var { return file.getFullPathName(); }
};

template <>
struct fmt::formatter<juce::File> : formatter<string_view> {
    template <typename FormatContext>
    auto format(juce::File const& file, FormatContext& ctx) const
    {
        return fmt::format_to(ctx.out(), "{}", file.getFullPathName());
    }
};
