#pragma once

namespace mc {

template <typename T>
struct HermiteInterpolation {
    [[nodiscard]] constexpr auto operator()(Span<T const, 4> val, T offset) const noexcept -> T;
};

template <typename T>
[[nodiscard]] constexpr auto samplesForHermiteInterpolation(Span<T const> buf, size_t s1) noexcept -> std::array<T, 4>;

} // namespace mc

#include "hermite_interpolation.ipp"
