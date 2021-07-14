#ifndef MODERN_CIRCUITS_JUCE_MODULES_TIME_UTILS_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_TIME_UTILS_HPP

template <>
struct juce::VariantConverter<juce::Time> {
    [[nodiscard]] static auto fromVar(juce::var const& v) -> juce::Time
    {
        return juce::Time::fromISO8601(v.toString());
    }

    [[nodiscard]] static auto toVar(juce::Time const& t) -> juce::var
    {
        auto str = t.toISO8601(true);
        return str;
    }
};

#endif // MODERN_CIRCUITS_JUCE_MODULES_TIME_UTILS_HPP
