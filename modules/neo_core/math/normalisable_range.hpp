// SPDX-License-Identifier: BSL-1.0

#pragma once

template <typename T>
struct juce::VariantConverter<juce::NormalisableRange<T>> {
    [[nodiscard]] static auto fromVar(juce::var const& v) -> juce::NormalisableRange<T>
    {
        auto const splits        = neo::strings::split(v.toString(), ':');
        auto const start         = neo::strings::toValue<T>(splits[0]);
        auto const end           = neo::strings::toValue<T>(splits[1]);
        auto const interval      = neo::strings::toValue<T>(splits[2]);
        auto const skew          = neo::strings::toValue<T>(splits[3]);
        auto const symmetricSkew = static_cast<int>(neo::strings::toValue<T>(splits[4])) == 1;
        return juce::NormalisableRange<T> { start, end, interval, skew, symmetricSkew };
    }

    [[nodiscard]] static auto toVar(juce::NormalisableRange<T> const& nr) -> juce::var
    {
        return neo::jformat("{}:{}:{}:{}:{}", nr.start, nr.end, nr.interval, nr.skew, nr.symmetricSkew);
    }
};
