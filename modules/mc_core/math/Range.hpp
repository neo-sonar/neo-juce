#pragma once

template <typename T>
struct juce::VariantConverter<juce::Range<T>> {
    MC_NODISCARD static auto fromVar(juce::var const& v) -> juce::Range<T>
    {
        auto const splits = mc::StringUtils::split(v.toString(), ':');
        auto const start  = mc::StringUtils::toValue<T>(splits[0]);
        auto const end    = mc::StringUtils::toValue<T>(splits[1]);
        return juce::Range<T> { start, end };
    }

    MC_NODISCARD static auto toVar(juce::Range<T> const& r) -> juce::var
    {
        return mc::jformat("{}:{}", r.getStart(), r.getEnd());
    }
};
