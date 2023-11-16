#pragma once

namespace neo {
[[nodiscard]] inline auto sizeAfterDownSample(std::size_t signalSize, std::size_t factor) noexcept -> std::size_t
{
    return (signalSize - 1U) / factor + 1U;
}

template <typename T>
inline auto downSample(T const* in, std::size_t sizeIn, T* out, std::size_t factor) -> std::size_t
{
    if (factor == 0) { std::ranges::copy(in, in + sizeIn, out); }
    auto const n = sizeAfterDownSample(sizeIn, factor);
    for (std::size_t i = 0; i < n; ++i) { out[i] = in[i * factor]; }
    return n;
}
} // namespace neo
