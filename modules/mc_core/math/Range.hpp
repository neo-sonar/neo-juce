#pragma once

template <typename T>
struct juce::VariantConverter<juce::Range<T>> {
    [[nodiscard]] static auto fromVar(juce::var const& v) -> juce::Range<T>
    {
        auto const splits = mc::strings::split(v.toString(), ':');
        auto const start  = mc::strings::toValue<T>(splits[0]);
        auto const end    = mc::strings::toValue<T>(splits[1]);
        return juce::Range<T> { start, end };
    }

    [[nodiscard]] static auto toVar(juce::Range<T> const& r) -> juce::var
    {
        return mc::jformat("{}:{}", r.getStart(), r.getEnd());
    }
};
