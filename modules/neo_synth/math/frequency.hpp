#pragma once

namespace neo {

template <typename T>
[[nodiscard]] constexpr auto hertzWithCentsOffset(T baseFrequencyHertz, T centsOffset) noexcept -> T
{
    return std::pow(T(2), centsOffset / T(1200)) * baseFrequencyHertz;
}

template <typename T>
[[nodiscard]] constexpr auto hertzWithSemitoneOffset(T baseFrequencyHertz, T semitonesOffset) noexcept -> T
{
    return hertzWithCentsOffset(baseFrequencyHertz, semitonesOffset * T(100));
}

} // namespace neo
