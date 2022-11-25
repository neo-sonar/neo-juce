#pragma once

namespace mc {

#if JUCE_MSVC && JUCE_DEBUG
    #pragma optimize("t", on)
#endif

template <typename T>
constexpr auto HermiteInterpolation<T>::operator()(Span<T const, 4> val, T offset) const noexcept -> T
{
    auto const slope0 = (val[2] - val[0]) * static_cast<T>(0.5);
    auto const slope1 = (val[3] - val[1]) * static_cast<T>(0.5);

    auto const v    = val[1] - val[2];
    auto const w    = slope0 + v;
    auto const a    = w + v + slope1;
    auto const bNeg = w + a;

    auto const stage1 = a * offset - bNeg;
    auto const stage2 = stage1 * offset + slope0;

    return stage2 * offset + val[1];
}

template <typename T>
auto HermiteInterpolation<xsimd::batch<T>>::operator()(Span<xsimd::batch<T> const, 4> val,
    xsimd::batch<T> offset) const noexcept -> xsimd::batch<T>
{
    auto const slope0 = (val[2] - val[0]) * static_cast<T>(0.5);
    auto const slope1 = (val[3] - val[1]) * static_cast<T>(0.5);

    auto const v    = val[1] - val[2];
    auto const w    = slope0 + v;
    auto const a    = w + v + slope1;
    auto const bNeg = w + a;

    auto const stage1 = xsimd::fms(a, offset, bNeg);
    auto const stage2 = xsimd::fma(stage1, offset, slope0);

    return xsimd::fma(stage2, offset, val[1]);
}

template <typename T>
constexpr auto samplesForHermiteInterpolation(Span<T const> buf, size_t s1) noexcept -> Array<T, 4>
{
    auto const size = buf.size();
    if (s1 == 0) { return { buf[0], buf[0], buf[1], buf[2] }; }
    if (s1 == size - 2) { return { buf[size - 3], buf[size - 2], buf[size - 1], buf[0] }; }
    if (s1 == size - 1) { return { buf[size - 2], buf[size - 1], buf[0], buf[1] }; }
    return { buf[s1 - 1], buf[s1], buf[s1 + 1], buf[s1 + 2] };
}

template <typename T>
auto samplesForHermiteInterpolation(Span<T const> buf, xsimd::batch<int32_t> s1) noexcept -> Array<xsimd::batch<T>, 4>
{
    auto const size = static_cast<int32_t>(buf.size());

    auto const s1IsSizeMinus2 = s1 == size - 2;
    auto const s1IsSizeMinus1 = s1 == size - 1;

    auto index0 = s1 - 1;
    auto index1 = s1;
    auto index2 = s1 + 1;
    auto index3 = s1 + 2;

    // s1 == 0
    index0 = xsimd::select(s1 == 0, xsimd::batch<int32_t> { size - 1 }, index0);

    // s1 == size - 2
    index0 = xsimd::select(s1IsSizeMinus2, xsimd::batch<int32_t> { size - 3 }, index0);
    index2 = xsimd::select(s1IsSizeMinus2, xsimd::batch<int32_t> { size - 1 }, index2);
    index3 = xsimd::select(s1IsSizeMinus2, xsimd::batch<int32_t> { 0 }, index3);

    // s1 == size - 1
    index0 = xsimd::select(s1IsSizeMinus1, xsimd::batch<int32_t> { size - 2 }, index0);
    index2 = xsimd::select(s1IsSizeMinus1, xsimd::batch<int32_t> { 0 }, index2);
    index3 = xsimd::select(s1IsSizeMinus1, xsimd::batch<int32_t> { 1 }, index3);

    return Array<xsimd::batch<T>, 4> {
        xsimd::batch<T>::gather(data(buf), index0),
        xsimd::batch<T>::gather(data(buf), index1),
        xsimd::batch<T>::gather(data(buf), index2),
        xsimd::batch<T>::gather(data(buf), index3),
    };
}

#if JUCE_MSVC && JUCE_DEBUG
    #pragma optimize("", on)
#endif

} // namespace mc
