// SPDX-License-Identifier: BSL-1.0

#pragma once

#if defined(__cpp_lib_span)

    #include <span>

namespace mc {
inline constexpr auto DynamicExtent = std::dynamic_extent;

template <typename T, std::size_t Extent = DynamicExtent>
using Span = std::span<T, Extent>;

    #if defined(__cpp_lib_byte)
using std::as_bytes;
using std::as_writable_bytes;
    #endif
} // namespace mc

#else

    #include <boost/core/span.hpp>

namespace mc {
inline constexpr auto DynamicExtent = boost::dynamic_extent;

template <typename T, std::size_t Extent = DynamicExtent>
using Span = boost::span<T, Extent>;

    #if defined(__cpp_lib_byte)
using boost::as_bytes;
using boost::as_writable_bytes;
    #endif
} // namespace mc

#endif

namespace mc {
inline auto makeSpan(juce::MemoryOutputStream const& out) -> Span<char const>
{
    return { static_cast<char const*>(out.getData()), out.getDataSize() };
}
} // namespace mc
