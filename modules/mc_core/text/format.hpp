#ifndef MODERN_CIRCUITS_JUCE_MODULES_FORMAT_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_FORMAT_HPP

namespace juce
{

inline auto to_string_view(juce::String const& string) -> ::fmt::string_view
{
    return ::fmt::string_view {string.begin(), static_cast<std::size_t>(string.length())};
}

}  // namespace juce

namespace mc
{

template<typename... Args>
[[nodiscard]] inline auto format(juce::String const& format_str, Args&&... args) -> juce::String
{
    return juce::String {::fmt::format(format_str, args...)};
}

}  // namespace mc

#endif  // MODERN_CIRCUITS_JUCE_MODULES_FORMAT_HPP
