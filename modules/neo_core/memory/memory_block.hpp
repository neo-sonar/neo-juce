// SPDX-License-Identifier: BSL-1.0
#pragma once

namespace neo {

[[nodiscard]] inline auto makeSpan(juce::MemoryBlock& block) -> std::span<std::byte>
{
    return { reinterpret_cast<std::byte*>(block.getData()), block.getSize() }; // NOLINT
}

[[nodiscard]] inline auto makeSpan(juce::MemoryBlock const& block) -> std::span<std::byte const>
{
    return { reinterpret_cast<std::byte const*>(block.getData()), block.getSize() }; // NOLINT
}

} // namespace neo
