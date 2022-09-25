#pragma once

template <typename ValueType>
struct juce::VariantConverter<juce::Point<ValueType>> {
    [[nodiscard]] static auto fromVar(juce::var const& v) -> juce::Point<ValueType>
    {
        auto const splits = mc::strings::split(v.toString(), ':');
        auto const x      = mc::strings::toValue<ValueType>(splits[0]);
        auto const y      = mc::strings::toValue<ValueType>(splits[1]);
        return juce::Point<ValueType> { x, y };
    }

    [[nodiscard]] static auto toVar(juce::Point<ValueType> const& p) -> juce::var
    {
        return mc::jformat("{}:{}", p.x, p.y);
    }
};
