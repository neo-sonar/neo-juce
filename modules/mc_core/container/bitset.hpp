// SPDX-License-Identifier: BSL-1.0

#pragma once

template <std::size_t Size>
struct juce::VariantConverter<std::bitset<Size>> {
    [[nodiscard]] static auto fromVar(juce::var const& v) -> std::bitset<Size>
    {
        return std::bitset<Size> { v.toString().toStdString() };
    }

    [[nodiscard]] static auto toVar(std::bitset<Size> const& bitset) -> juce::var
    {
        return juce::String { bitset.to_string() };
    }
};
