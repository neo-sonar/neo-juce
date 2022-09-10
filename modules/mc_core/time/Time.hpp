#pragma once

template <>
struct juce::VariantConverter<juce::Time> {
    MC_NODISCARD static auto fromVar(juce::var const& v) -> juce::Time { return juce::Time::fromISO8601(v.toString()); }

    MC_NODISCARD static auto toVar(juce::Time const& t) -> juce::var
    {
        auto str = t.toISO8601(true);
        return str;
    }
};
