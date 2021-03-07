namespace mc
{

ModulatorMacro::ModulatorMacro(juce::ValueTree valueTree, juce::UndoManager* undoManager)
    : Modulator {std::move(valueTree), undoManager}
{
}

auto ModulatorMacro::getName() const -> juce::String { return "Macro"; }

auto ModulatorMacro::prepareToPlay(double sampleRate, int maxSamplesPerBlock) -> void
{
    juce::ignoreUnused(sampleRate, maxSamplesPerBlock);
}

auto ModulatorMacro::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiBuffer) -> void
{
    juce::ignoreUnused(buffer, midiBuffer);
}

auto ModulatorMacro::releaseResources() -> void { }

}  // namespace mc