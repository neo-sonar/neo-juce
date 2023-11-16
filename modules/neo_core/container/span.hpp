// SPDX-License-Identifier: BSL-1.0

#pragma once

namespace neo {
inline auto makeSpan(juce::MemoryOutputStream const& out) -> std::span<char const>
{
    return { static_cast<char const*>(out.getData()), out.getDataSize() };
}
} // namespace neo
