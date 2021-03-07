namespace mc
{

ModulatorMacro::ModulatorMacro(juce::ValueTree valueTree, juce::UndoManager* undoManager)
    : Modulator {std::move(valueTree), undoManager}
    , gain_ {getValueTree(), ModulatorMacroIDs::gain, getUndoManager(), 1.0f}
{
    jassert(getValueTree().hasType(ModulatorMacroIDs::type));
}

auto ModulatorMacro::getName() const -> juce::String { return "Macro"; }

auto ModulatorMacro::prepareToPlay(double sampleRate, int maxSamplesPerBlock) -> void
{
    juce::ignoreUnused(sampleRate, maxSamplesPerBlock);
}

auto ModulatorMacro::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiBuffer) -> void
{
    juce::ignoreUnused(midiBuffer);
    jassert(buffer.getNumChannels() == 1);

    auto const gain    = static_cast<float>(gain_.get());
    auto* const output = buffer.getWritePointer(0);
    for (auto i = 0; i < buffer.getNumSamples(); ++i) { output[i] = gain; }
}

auto ModulatorMacro::releaseResources() -> void { }

auto ModulatorMacro::setGain(float newGain) -> void { gain_ = newGain; }

auto ModulatorMacro::getGain() const -> float { return gain_.get(); }

}  // namespace mc