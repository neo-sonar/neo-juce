#pragma once

template <typename ValueType>
struct juce::VariantConverter<juce::Line<ValueType>> {
    [[nodiscard]] static auto fromVar(juce::var const& v) -> juce::Line<ValueType>
    {
        auto const splits = mc::strings::split(v.toString(), ':');
        auto const startX = mc::strings::toValue<ValueType>(splits[0]);
        auto const startY = mc::strings::toValue<ValueType>(splits[1]);
        auto const endX   = mc::strings::toValue<ValueType>(splits[2]);
        auto const endY   = mc::strings::toValue<ValueType>(splits[3]);
        return juce::Line<ValueType> { { startX, startY }, { endX, endY } };
    }

    [[nodiscard]] static auto toVar(juce::Line<ValueType> const& l) -> juce::var
    {
        return mc::jformat("{}:{}:{}:{}", l.getStart().x, l.getStart().y, l.getEnd().x, l.getEnd().y);
    }
};
