// SPDX-License-Identifier: BSL-1.0
#pragma once

namespace neo {

[[nodiscard]] auto hasMagicHeader(juce::File const& file, std::span<char const> header) -> bool;
[[nodiscard]] auto hasMagicHeader(juce::InputStream& in, std::span<char const> header) -> bool;
[[nodiscard]] auto hasMagicHeader(std::span<char const> content, std::span<char const> header) -> bool;

} // namespace neo
