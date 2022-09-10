#pragma once

namespace mc {

struct MouseEventUtils {
    ~MouseEventUtils() = delete;

    MC_NODISCARD static auto hitTest(juce::MouseEvent const& event, juce::Rectangle<float> bounds) -> bool;
    MC_NODISCARD static auto hitTest(juce::MouseEvent const& event, juce::Point<float> point, float radius) -> bool;
};

} // namespace mc
