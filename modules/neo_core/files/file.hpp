// SPDX-License-Identifier: BSL-1.0

#pragma once

namespace neo {
[[nodiscard]] auto makeFile(juce::StringRef relativeOrAbsolutePath) -> juce::File;
[[nodiscard]] auto makeTemporaryDirectory(juce::StringRef name) -> juce::File;
[[nodiscard]] auto makeChildDirectory(juce::File const& parent, juce::StringRef name) -> juce::File;
[[nodiscard]] auto copyFile(juce::File const& src, juce::File const& dest) -> juce::Result;
[[nodiscard]] auto loadFileAsBytes(juce::File const& file) -> std::vector<std::byte>;
} // namespace neo

template <>
struct juce::VariantConverter<juce::File> {
    [[nodiscard]] static auto fromVar(juce::var const& v) -> juce::File;
    [[nodiscard]] static auto toVar(juce::File const& file) -> juce::var;
};

template <>
struct fmt::formatter<juce::File> : formatter<string_view> {
    template <typename FormatContext>
    auto format(juce::File const& file, FormatContext& ctx) const
    {
        return fmt::format_to(ctx.out(), "{}", file.getFullPathName());
    }
};
