// SPDX-License-Identifier: BSL-1.0

#pragma once

namespace mc {

auto RangeUtils::defaultNormalizedRange() noexcept -> juce::NormalisableRange<float>
{
    auto range = juce::NormalisableRange<float> { 0.0F, 1.0F, 0.01F };
    return range;
}

auto RangeUtils::defaultGainRange() noexcept -> juce::NormalisableRange<float>
{
    auto range = juce::NormalisableRange<float> { 0.0F, 4.0F, 0.01F };
    range.setSkewForCentre(1.0F);
    return range;
}

auto RangeUtils::defaultFrequencyRange() noexcept -> juce::NormalisableRange<float>
{
    auto range = juce::NormalisableRange<float> { 20.0F, 22'000.0F, 1.0F };
    range.setSkewForCentre(3'000.0F);
    return range;
}

auto RangeUtils::defaultTimeRange() noexcept -> juce::NormalisableRange<float>
{
    auto range = juce::NormalisableRange<float> { 0.0F, 2000.0F, 0.1F };
    range.setSkewForCentre(100.F);
    return range;
}

} // namespace mc
