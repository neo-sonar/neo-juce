namespace neo {
namespace {
template <typename T>
auto getParameter(juce::AudioProcessorValueTreeState& vts, juce::StringRef id) -> T
{
    auto* raw       = vts.getParameter(id);
    auto* parameter = dynamic_cast<T>(raw);
    return parameter;
}
} // namespace

auto getFloatParameter(juce::AudioProcessorValueTreeState& vts, juce::StringRef id) -> juce::AudioParameterFloat*
{
    return getParameter<juce::AudioParameterFloat*>(vts, id);
}

auto getChoiceParameter(juce::AudioProcessorValueTreeState& vts, juce::StringRef id) -> juce::AudioParameterChoice*
{
    return getParameter<juce::AudioParameterChoice*>(vts, id);
}

auto getIntParameter(juce::AudioProcessorValueTreeState& vts, juce::StringRef id) -> juce::AudioParameterInt*
{
    return getParameter<juce::AudioParameterInt*>(vts, id);
}

auto getBoolParameter(juce::AudioProcessorValueTreeState& vts, juce::StringRef id) -> juce::AudioParameterBool*
{
    return getParameter<juce::AudioParameterBool*>(vts, id);
}

} // namespace neo
