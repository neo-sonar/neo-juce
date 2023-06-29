// SPDX-License-Identifier: BSL-1.0

/*
BEGIN_JUCE_MODULE_DECLARATION

    ID:                 mc_core
    vendor:             Modern Circuits
    version:            0.1.0
    name:               Modern Circuits JUCE Core module
    description:        Core JUCE extensions and utilities.
    dependencies:       juce_core
    website:            http://github.com/ModernCircuits/mc-juce
    license:            BSL-1.0
    minimumCppStandard: 20

END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_MC_CORE
    #define USE_MC_CORE
#endif

#include <juce_core/juce_core.h>

#include <bitset>
#include <optional>
#include <queue>

#include <fmt/format.h>
#include <fmt/os.h>
#include <fmt/ostream.h>

#include <boost/container/static_vector.hpp>
#include <range/v3/all.hpp>

namespace mc {
template <typename T>
struct ThreadSafeQueue {

    using value_type = T;
    using size_type  = typename std::queue<T>::size_type;

    ThreadSafeQueue()  = default;
    ~ThreadSafeQueue() = default;

    ThreadSafeQueue(ThreadSafeQueue const&)                    = delete;
    auto operator=(ThreadSafeQueue const&) -> ThreadSafeQueue& = delete;

    ThreadSafeQueue(ThreadSafeQueue&& other)              = delete;
    auto operator=(ThreadSafeQueue&&) -> ThreadSafeQueue& = delete;

    [[nodiscard]] auto pop() -> std::optional<value_type>
    {
        std::lock_guard<std::mutex> const lock(_mutex);
        if (_queue.empty()) { return std::nullopt; }
        value_type tmp = _queue.front();
        _queue.pop();
        return tmp;
    }

    auto push(value_type const& item) -> void
    {
        std::lock_guard<std::mutex> const lock(_mutex);
        _queue.push(item);
    }

    auto push(value_type&& item) -> void
    {
        std::lock_guard<std::mutex> const lock(_mutex);
        _queue.push(std::move(item));
    }

    [[nodiscard]] auto size() const -> size_type
    {
        std::lock_guard<std::mutex> const lock(_mutex);
        return _queue.size();
    }

private:
    // Moved out of public interface to prevent races between this and pop().
    [[nodiscard]] auto empty() const -> bool { return _queue.empty(); }

    std::queue<value_type> _queue {};
    std::mutex mutable _mutex {};
};
} // namespace mc

namespace mc {

template <typename T, std::size_t Capacity>
using StaticVector = boost::container::static_vector<T, Capacity>;
} // namespace mc

#if defined(__cpp_lib_span)

    #include <span>

namespace mc {
/// \ingroup group-containers
inline constexpr auto DynamicExtent = std::dynamic_extent;

/// \ingroup group-containers
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
/// \ingroup group-containers
inline constexpr auto DynamicExtent = boost::dynamic_extent;

/// \ingroup group-containers
template <typename T, std::size_t Extent = DynamicExtent>
using Span = boost::span<T, Extent>;

    #if defined(__cpp_lib_byte)
using boost::as_bytes;
using boost::as_writable_bytes;
    #endif
} // namespace mc

#endif

#if JUCE_MSVC
    #pragma warning(push)
    #pragma warning(disable : 4702) // unreachable code
#endif

#include <moodycamel/concurrentqueue.h>

#if JUCE_MSVC
    #pragma warning(pop)
#endif

namespace mc {
template <typename T>
using LockFreeQueue = moodycamel::ConcurrentQueue<T>;
}

namespace mc {

/// \brief Duration.
/// \ingroup group-units
template <typename T, typename R>
using Duration = std::chrono::duration<T, R>;

/// \brief Duration in microseconds.
/// \ingroup group-units
template <typename T>
using Microseconds = Duration<T, std::micro>;

/// \brief Duration in milliseconds.
/// \ingroup group-units
template <typename T>
using Milliseconds = Duration<T, std::milli>;

/// \brief Duration in seconds.
/// \ingroup group-units
template <typename T>
using Seconds = Duration<T, std::ratio<1>>;

/// \brief Converts a duration to milliseconds.
/// \ingroup group-units
template <typename T, typename R>
[[nodiscard]] constexpr auto toMilliseconds(Duration<T, R> const& d) noexcept
{
    return std::chrono::duration_cast<Milliseconds<T>>(d);
}

/// \brief Converts a duration to seconds.
/// \ingroup group-units
template <typename T, typename R>
[[nodiscard]] constexpr auto toSeconds(Duration<T, R> const& d) noexcept
{
    return std::chrono::duration_cast<Seconds<T>>(d);
}

} // namespace mc

#include <boost/container/flat_map.hpp>

namespace mc {

/// \ingroup group-containers
template <typename Key,
    typename T,
    typename Compare              = std::less<Key>,
    typename AllocatorOrContainer = boost::container::new_allocator<std::pair<Key, T>>>
using FlatMap = boost::container::flat_map<Key, T, Compare, AllocatorOrContainer>;

} // namespace mc

// #include <mc/core/random.hpp>
// #include <mc/core/scope.hpp>

#include "text/jformat.hpp"
#include "text/string.hpp"
#include "text/strings.hpp"

#include "container/array.hpp"
#include "container/bitset.hpp"
#include "container/registry.hpp"
#include "container/span.hpp"
#include "container/string_array.hpp"
#include "files/file.hpp"
#include "files/zip_file.hpp"
#include "javascript/json_utils.hpp"
#include "math/normalisable_range.hpp"
#include "math/range.hpp"
#include "memory/memory_block.hpp"
#include "misc/result.hpp"
#include "time/duration.hpp"
#include "time/time.hpp"
