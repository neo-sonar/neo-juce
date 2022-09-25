#pragma once

namespace mc {
inline auto makeSpan(juce::MemoryOutputStream const& out) -> Span<char const>
{
    return { static_cast<char const*>(out.getData()), out.getDataSize() };
}
} // namespace mc
