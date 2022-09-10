#pragma once

namespace mc {

template <typename T>
MC_NODISCARD auto toString(T& obj) -> decltype(obj.toString())
{
    return obj.toString();
}

template <typename T>
MC_NODISCARD auto toString(T const& obj) -> decltype(obj.toString())
{
    return obj.toString();
}

} // namespace mc
