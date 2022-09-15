#pragma once

namespace mc {

struct MouseEventUtils {
    ~MouseEventUtils() = delete;

    [[nodiscard]] static auto hitTest(juce::MouseEvent const& event, juce::Rectangle<float> bounds) -> bool;
    [[nodiscard]] static auto hitTest(juce::MouseEvent const& event, juce::Point<float> point, float radius) -> bool;
};

} // namespace mc
