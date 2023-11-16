#pragma once

namespace neo {
template <typename T>
static auto rmsError(std::span<T const> lhs, std::span<T const> rhs) -> T
{
    if (lhs.size() != rhs.size()) { throw std::invalid_argument { "signals must have the same size" }; }

    auto diffSquared = [](auto x, auto y) {
        auto const diff = x - y;
        return diff * diff;
    };

    auto sum   = std::transform_reduce(lhs.begin(), lhs.end(), rhs.begin(), T {}, std::plus<> {}, diffSquared);
    auto error = std::sqrt(sum / static_cast<T>(lhs.size() - 1));

    return error;
}

} // namespace neo
