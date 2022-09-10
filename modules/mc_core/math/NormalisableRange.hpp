#pragma once

template <typename T>
struct juce::VariantConverter<juce::NormalisableRange<T>> {
    MC_NODISCARD static auto fromVar(juce::var const& v) -> juce::NormalisableRange<T>
    {
        auto const splits        = mc::StringUtils::split(v.toString(), ':');
        auto const start         = mc::StringUtils::toValue<T>(splits[0]);
        auto const end           = mc::StringUtils::toValue<T>(splits[1]);
        auto const interval      = mc::StringUtils::toValue<T>(splits[2]);
        auto const skew          = mc::StringUtils::toValue<T>(splits[3]);
        auto const symmetricSkew = static_cast<int>(mc::StringUtils::toValue<T>(splits[4])) == 1;
        return juce::NormalisableRange<T> { start, end, interval, skew, symmetricSkew };
    }

    MC_NODISCARD static auto toVar(juce::NormalisableRange<T> const& nr) -> juce::var
    {
        return mc::jformat("{}:{}:{}:{}:{}", nr.start, nr.end, nr.interval, nr.skew, nr.symmetricSkew);
    }
};
