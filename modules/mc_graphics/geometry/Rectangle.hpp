#pragma once

template <typename ValueType>
struct juce::VariantConverter<juce::Rectangle<ValueType>> {
    [[nodiscard]] static auto fromVar(juce::var const& v) -> juce::Rectangle<ValueType>
    {
        auto const splits = mc::strings::split(v.toString(), ':');
        auto const x      = mc::strings::toValue<ValueType>(splits[0]);
        auto const y      = mc::strings::toValue<ValueType>(splits[1]);
        auto const width  = mc::strings::toValue<ValueType>(splits[2]);
        auto const height = mc::strings::toValue<ValueType>(splits[3]);
        return juce::Rectangle<ValueType> { x, y, width, height };
    }

    [[nodiscard]] static auto toVar(juce::Rectangle<ValueType> const& l) -> juce::var
    {
        return mc::jformat("{}:{}:{}:{}", l.getX(), l.getY(), l.getWidth(), l.getHeight());
    }
};
