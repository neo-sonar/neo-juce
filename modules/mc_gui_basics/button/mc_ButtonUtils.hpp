#ifndef MODERN_CIRCUITS_JUCE_MODULES_BUTTON_UTILS_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_BUTTON_UTILS_HPP

namespace mc
{

/**
 * @brief Helper functions for button components.
 */
struct ButtonUtils
{
    /**
     * @brief Maps a svg image to a button component.
     */
    static auto mapSVG(juce::DrawableButton& button, char const* svgData, size_t svgSize, juce::Colour color) -> void;
};

}  // namespace mc

#endif  // MODERN_CIRCUITS_JUCE_MODULES_BUTTON_UTILS_HPP
