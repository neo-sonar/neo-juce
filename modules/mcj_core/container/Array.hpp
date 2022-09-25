// SPDX-License-Identifier: BSL-1.0

#pragma once

namespace mc {

template <typename T>
auto fillJuceArray(T const& obj, int count) -> juce::Array<T>
{
    auto array = juce::Array<T> {};
    array.ensureStorageAllocated(count);
    for (auto i { 0 }; i < count; ++i) { array.add(obj); }
    return array;
}

} // namespace mc
