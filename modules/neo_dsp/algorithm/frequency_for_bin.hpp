#pragma once

namespace neo {
template <typename T, typename U, typename V>
[[nodiscard]] constexpr auto frequencyForBin(U windowSize, V index, double sampleRate) -> T
{
    static_assert(std::is_integral_v<U>);
    static_assert(std::is_integral_v<V>);

    return static_cast<T>(index) * static_cast<T>(sampleRate) / static_cast<T>(windowSize);
}
} // namespace neo
