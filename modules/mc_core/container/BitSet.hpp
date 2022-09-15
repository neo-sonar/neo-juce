#pragma once

template <std::size_t Size>
struct juce::VariantConverter<mc::BitSet<Size>> {
    [[nodiscard]] static auto fromVar(juce::var const& v) -> mc::BitSet<Size>
    {
        return mc::BitSet<Size> { v.toString().toStdString() };
    }

    [[nodiscard]] static auto toVar(mc::BitSet<Size> const& bitset) -> juce::var
    {
        return juce::String { bitset.to_string() };
    }
};
