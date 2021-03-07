#ifndef MODERN_CIRCUITS_JUCE_MODULES_COLOR_UTILS_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_COLOR_UTILS_HPP

template<>
struct juce::VariantConverter<juce::Colour>
{
    [[nodiscard]] static auto fromVar(juce::var const& v) -> juce::Colour { return Colour::fromString(v.toString()); }
    [[nodiscard]] static auto toVar(juce::Colour const& c) -> juce::var { return c.toString(); }
};

#endif  // MODERN_CIRCUITS_JUCE_MODULES_COLOR_UTILS_HPP
