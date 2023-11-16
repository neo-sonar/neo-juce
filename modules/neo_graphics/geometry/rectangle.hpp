#pragma once

template <typename ValueType>
struct juce::VariantConverter<juce::Rectangle<ValueType>> {
    [[nodiscard]] static auto fromVar(juce::var const& v) -> juce::Rectangle<ValueType>
    {
        auto const splits = neo::strings::split(v.toString(), ':');
        auto const x      = neo::strings::toValue<ValueType>(splits[0]);
        auto const y      = neo::strings::toValue<ValueType>(splits[1]);
        auto const width  = neo::strings::toValue<ValueType>(splits[2]);
        auto const height = neo::strings::toValue<ValueType>(splits[3]);
        return juce::Rectangle<ValueType> { x, y, width, height };
    }

    [[nodiscard]] static auto toVar(juce::Rectangle<ValueType> const& l) -> juce::var
    {
        return neo::jformat("{}:{}:{}:{}", l.getX(), l.getY(), l.getWidth(), l.getHeight());
    }
};
