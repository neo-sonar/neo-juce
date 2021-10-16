#pragma once

namespace mc {

auto drawRoundedBorder(juce::Graphics& g, juce::Rectangle<int> area, juce::Colour color) -> void;
auto drawRoundedBorder(juce::Graphics& g, juce::Rectangle<float> area, juce::Colour color) -> void;
auto drawRoundedBorder(juce::Graphics& g, juce::Component& component, juce::Colour color) -> void;

} // namespace mc