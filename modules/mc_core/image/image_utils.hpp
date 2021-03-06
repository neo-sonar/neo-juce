#ifndef MODERN_CIRCUITS_APP_ZENTRALE_IMAGE_UTILS_HPP
#define MODERN_CIRCUITS_APP_ZENTRALE_IMAGE_UTILS_HPP

namespace mc
{
struct ImageUtils
{
    [[nodiscard]] static auto loadFromURL(juce::URL const& url) -> juce::Image;
};
}  // namespace mc

#endif  // MODERN_CIRCUITS_APP_ZENTRALE_IMAGE_UTILS_HPP
