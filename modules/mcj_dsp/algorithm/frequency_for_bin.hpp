#pragma once

namespace mc {
template <typename T>
[[nodiscard]] constexpr auto frequencyForBin(size_t windowSize, size_t index, double sampleRate) -> T
{
    return static_cast<T>(index) * static_cast<T>(sampleRate) / static_cast<T>(windowSize);
}
} // namespace mc
