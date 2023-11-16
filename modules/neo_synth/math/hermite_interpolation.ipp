#pragma once

namespace neo {

#if JUCE_MSVC && JUCE_DEBUG
    #pragma optimize("t", on)
#endif

template <typename T>
constexpr auto HermiteInterpolation<T>::operator()(std::span<T const, 4> val, T offset) const noexcept -> T
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
constexpr auto samplesForHermiteInterpolation(std::span<T const> buf, size_t s1) noexcept -> std::array<T, 4>
{
    auto const size = buf.size();
    if (s1 == 0) { return { buf[0], buf[0], buf[1], buf[2] }; }
    if (s1 == size - 2) { return { buf[size - 3], buf[size - 2], buf[size - 1], buf[0] }; }
    if (s1 == size - 1) { return { buf[size - 2], buf[size - 1], buf[0], buf[1] }; }
    return { buf[s1 - 1], buf[s1], buf[s1 + 1], buf[s1 + 2] };
}

#if JUCE_MSVC && JUCE_DEBUG
    #pragma optimize("", on)
#endif

} // namespace neo
