#ifndef MODERN_CIRCUITS_JUCE_MODULES_FORMAT_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_FORMAT_HPP

namespace juce {

inline auto to_string_view(juce::String const& string) -> ::fmt::string_view // NOLINT(readability-identifier-naming)
{
    return ::fmt::string_view { string.begin(), static_cast<std::size_t>(string.length()) };
}

} // namespace juce

namespace mc {

template <typename... Args>
MC_NODISCARD inline auto jformat(juce::String const& formatStr, Args&&... args) -> juce::String
{
    return juce::String { format(to_string_view(formatStr), args...) };
}

} // namespace mc

#endif // MODERN_CIRCUITS_JUCE_MODULES_FORMAT_HPP
