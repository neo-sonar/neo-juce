// SPDX-License-Identifier: BSL-1.0

#pragma once

namespace mc {

template <typename T>
auto DefaultRange<T>::normalized() -> juce::NormalisableRange<T>
{
    auto range = juce::NormalisableRange<T> { T(0), T(1) };
    return range;
}

template <typename T>
auto DefaultRange<T>::gain() -> juce::NormalisableRange<T>
{
    auto range = juce::NormalisableRange<T> { T(0), T(4) };
    range.setSkewForCentre(T(1));
    return range;
}

template <typename T>
auto DefaultRange<T>::frequency() -> juce::NormalisableRange<T>
{
    auto range = juce::NormalisableRange<T> { T(20), T(20'000) };
    range.setSkewForCentre(T(700));
    return range;
}

template <typename T>
auto DefaultRange<T>::timeMilliseconds() -> juce::NormalisableRange<T>
{
    auto range = juce::NormalisableRange<T> { T(0), T(2000) };
    range.setSkewForCentre(T(100));
    return range;
}

} // namespace mc
