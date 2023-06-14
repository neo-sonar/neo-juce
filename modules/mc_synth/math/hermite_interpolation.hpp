#pragma once

namespace mc {

template <typename T>
struct HermiteInterpolation {
    [[nodiscard]] constexpr auto operator()(Span<T const, 4> val, T offset) const noexcept -> T;
};

template <typename T>
struct HermiteInterpolation<xsimd::batch<T>> {

    [[nodiscard]] auto operator()(Span<xsimd::batch<T> const, 4> val, xsimd::batch<T> offset) const noexcept
        -> xsimd::batch<T>;
};

template <typename T>
[[nodiscard]] constexpr auto samplesForHermiteInterpolation(Span<T const> buf, size_t s1) noexcept -> std::array<T, 4>;

template <typename T>
[[nodiscard]] auto samplesForHermiteInterpolation(Span<T const> buf, xsimd::batch<int32_t> s1) noexcept
    -> std::array<xsimd::batch<T>, 4>;

} // namespace mc

#include "hermite_interpolation.ipp"
