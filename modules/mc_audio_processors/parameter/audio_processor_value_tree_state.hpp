#pragma once

namespace mc {

[[nodiscard]] auto getFloatParameter(juce::AudioProcessorValueTreeState& vts, juce::StringRef id)
    -> juce::AudioParameterFloat*;

[[nodiscard]] auto getChoiceParameter(juce::AudioProcessorValueTreeState& vts, juce::StringRef id)
    -> juce::AudioParameterChoice*;

[[nodiscard]] auto getIntParameter(juce::AudioProcessorValueTreeState& vts, juce::StringRef id)
    -> juce::AudioParameterInt*;

[[nodiscard]] auto getBoolParameter(juce::AudioProcessorValueTreeState& vts, juce::StringRef id)
    -> juce::AudioParameterBool*;

} // namespace mc
