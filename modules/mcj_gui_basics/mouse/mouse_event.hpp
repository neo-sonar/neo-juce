#pragma once

namespace mc {
[[nodiscard]] auto hitTest(juce::MouseEvent const& event, juce::Rectangle<float> bounds) -> bool;
[[nodiscard]] auto hitTest(juce::MouseEvent const& event, juce::Point<float> point, float radius) -> bool;
} // namespace mc
