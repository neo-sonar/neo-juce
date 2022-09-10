#pragma once

template <typename ValueType>
struct juce::VariantConverter<juce::Rectangle<ValueType>> {
    MC_NODISCARD static auto fromVar(juce::var const& v) -> juce::Rectangle<ValueType>
    {
        auto const splits = mc::StringUtils::split(v.toString(), ':');
        auto const x      = mc::StringUtils::toValue<ValueType>(splits[0]);
        auto const y      = mc::StringUtils::toValue<ValueType>(splits[1]);
        auto const width  = mc::StringUtils::toValue<ValueType>(splits[2]);
        auto const height = mc::StringUtils::toValue<ValueType>(splits[3]);
        return juce::Rectangle<ValueType> { x, y, width, height };
    }

    MC_NODISCARD static auto toVar(juce::Rectangle<ValueType> const& l) -> juce::var
    {
        return mc::jformat("{}:{}:{}:{}", l.getX(), l.getY(), l.getWidth(), l.getHeight());
    }
};
