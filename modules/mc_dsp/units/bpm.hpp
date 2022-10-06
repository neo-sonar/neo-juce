#pragma once

namespace mc {
template <typename T>
[[nodiscard]] constexpr auto bpmToHertz(T bpm) noexcept -> T
{
    return bpm / T { 60 };
}
} // namespace mc
