#ifndef MODERN_CIRCUITS_JUCE_MODULES_FORMAT_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_FORMAT_HPP

namespace mc
{
[[nodiscard]] inline auto format(juce::String const& format) -> juce::String { return format + juce::String {143}; }
}  // namespace mc

#endif  // MODERN_CIRCUITS_JUCE_MODULES_FORMAT_HPP
