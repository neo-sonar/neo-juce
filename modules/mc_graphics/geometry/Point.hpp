#pragma once

template <typename ValueType>
struct juce::VariantConverter<juce::Point<ValueType>> {
    MC_NODISCARD static auto fromVar(juce::var const& v) -> juce::Point<ValueType>
    {
        auto const splits = mc::StringUtils::split(v.toString(), ':');
        auto const x      = mc::StringUtils::toValue<ValueType>(splits[0]);
        auto const y      = mc::StringUtils::toValue<ValueType>(splits[1]);
        return juce::Point<ValueType> { x, y };
    }

    MC_NODISCARD static auto toVar(juce::Point<ValueType> const& p) -> juce::var
    {
        return mc::jformat("{}:{}", p.x, p.y);
    }
};
