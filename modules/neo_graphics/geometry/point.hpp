#pragma once

template <typename ValueType>
struct juce::VariantConverter<juce::Point<ValueType>> {
    [[nodiscard]] static auto fromVar(juce::var const& v) -> juce::Point<ValueType>
    {
        auto const splits = neo::strings::split(v.toString(), ':');
        auto const x      = neo::strings::toValue<ValueType>(splits[0]);
        auto const y      = neo::strings::toValue<ValueType>(splits[1]);
        return juce::Point<ValueType> { x, y };
    }

    [[nodiscard]] static auto toVar(juce::Point<ValueType> const& p) -> juce::var
    {
        return neo::jformat("{}:{}", p.x, p.y);
    }
};
