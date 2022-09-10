#pragma once

template <typename ValueType>
struct juce::VariantConverter<juce::Line<ValueType>> {
    MC_NODISCARD static auto fromVar(juce::var const& v) -> juce::Line<ValueType>
    {
        auto const splits = mc::StringUtils::split(v.toString(), ':');
        auto const startX = mc::StringUtils::toValue<ValueType>(splits[0]);
        auto const startY = mc::StringUtils::toValue<ValueType>(splits[1]);
        auto const endX   = mc::StringUtils::toValue<ValueType>(splits[2]);
        auto const endY   = mc::StringUtils::toValue<ValueType>(splits[3]);
        return juce::Line<ValueType> { { startX, startY }, { endX, endY } };
    }

    MC_NODISCARD static auto toVar(juce::Line<ValueType> const& l) -> juce::var
    {
        return mc::jformat("{}:{}:{}:{}", l.getStart().x, l.getStart().y, l.getEnd().x, l.getEnd().y);
    }
};
