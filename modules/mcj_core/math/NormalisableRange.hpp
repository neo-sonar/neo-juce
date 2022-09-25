#pragma once

template <typename T>
struct juce::VariantConverter<juce::NormalisableRange<T>> {
    [[nodiscard]] static auto fromVar(juce::var const& v) -> juce::NormalisableRange<T>
    {
        auto const splits        = mc::strings::split(v.toString(), ':');
        auto const start         = mc::strings::toValue<T>(splits[0]);
        auto const end           = mc::strings::toValue<T>(splits[1]);
        auto const interval      = mc::strings::toValue<T>(splits[2]);
        auto const skew          = mc::strings::toValue<T>(splits[3]);
        auto const symmetricSkew = static_cast<int>(mc::strings::toValue<T>(splits[4])) == 1;
        return juce::NormalisableRange<T> { start, end, interval, skew, symmetricSkew };
    }

    [[nodiscard]] static auto toVar(juce::NormalisableRange<T> const& nr) -> juce::var
    {
        return mc::jformat("{}:{}:{}:{}:{}", nr.start, nr.end, nr.interval, nr.skew, nr.symmetricSkew);
    }
};
