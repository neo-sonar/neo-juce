#pragma once

namespace mc {
auto getFloatParameter(juce::AudioProcessorValueTreeState& vts, juce::StringRef id) -> juce::AudioParameterFloat*;
auto getChoiceParameter(juce::AudioProcessorValueTreeState& vts, juce::StringRef id) -> juce::AudioParameterChoice*;
auto getIntParameter(juce::AudioProcessorValueTreeState& vts, juce::StringRef id) -> juce::AudioParameterInt*;
auto getBoolParameter(juce::AudioProcessorValueTreeState& vts, juce::StringRef id) -> juce::AudioParameterBool*;
} // namespace mc
