#ifndef MODERN_CIRCUITS_JUCE_MODULES_COLOR_UTILS_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_COLOR_UTILS_HPP

namespace mc
{
inline auto makeColor(int r, int g, int b) -> juce::Colour
{
    jassert(r <= 255);
    jassert(g <= 255);
    jassert(b <= 255);
    return juce::Colour(static_cast<uint8_t>(r), static_cast<uint8_t>(g), static_cast<uint8_t>(b));
}
}  // namespace mc

template<>
struct juce::VariantConverter<juce::Colour>
{
    [[nodiscard]] static auto fromVar(juce::var const& v) -> juce::Colour { return Colour::fromString(v.toString()); }
    [[nodiscard]] static auto toVar(juce::Colour const& c) -> juce::var { return c.toString(); }
};

#endif  // MODERN_CIRCUITS_JUCE_MODULES_COLOR_UTILS_HPP
