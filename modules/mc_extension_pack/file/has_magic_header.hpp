// SPDX-License-Identifier: BSL-1.0
#pragma once

namespace mc {

[[nodiscard]] auto hasMagicHeader(juce::File const& file, Span<char const> header) -> bool;
[[nodiscard]] auto hasMagicHeader(juce::InputStream& in, Span<char const> header) -> bool;
[[nodiscard]] auto hasMagicHeader(Span<char const> content, Span<char const> header) -> bool;

} // namespace mc
