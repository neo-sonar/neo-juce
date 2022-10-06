// SPDX-License-Identifier: BSL-1.0
#pragma once

namespace mc {

[[nodiscard]] inline auto makeSpan(juce::MemoryBlock& block) -> Span<Byte>
{
    return { reinterpret_cast<Byte*>(block.getData()), block.getSize() }; // NOLINT
}

[[nodiscard]] inline auto makeSpan(juce::MemoryBlock const& block) -> Span<Byte const>
{
    return { reinterpret_cast<Byte const*>(block.getData()), block.getSize() }; // NOLINT
}

} // namespace mc
