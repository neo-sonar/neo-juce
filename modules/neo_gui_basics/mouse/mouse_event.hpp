#pragma once

namespace neo {
[[nodiscard]] auto hitTest(juce::MouseEvent const& event, juce::Rectangle<float> bounds) -> bool;
[[nodiscard]] auto hitTest(juce::MouseEvent const& event, juce::Point<float> point, float radius) -> bool;
} // namespace neo
