#ifndef MODERN_CIRCUITS_APP_ZENTRALE_JSON_UTILS_HPP
#define MODERN_CIRCUITS_APP_ZENTRALE_JSON_UTILS_HPP

namespace mc
{

struct JSONUtils
{
    [[nodiscard]] static auto loadFromURL(juce::URL const& url) -> juce::var;
};

}  // namespace mc
#endif  // MODERN_CIRCUITS_APP_ZENTRALE_JSON_UTILS_HPP
