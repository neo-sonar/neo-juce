#ifndef MODERN_CIRCUITS_JUCE_MODULES_MOUSE_UTILS_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_MOUSE_UTILS_HPP

namespace mc {

struct MouseEventUtils {
    ~MouseEventUtils() = delete;

    MC_NODISCARD static auto hitTest(juce::MouseEvent const& event, juce::Rectangle<float> bounds) -> bool;
    MC_NODISCARD static auto hitTest(juce::MouseEvent const& event, juce::Point<float> point, float radius) -> bool;
};

} // namespace mc

#endif // MODERN_CIRCUITS_JUCE_MODULES_MOUSE_UTILS_HPP
