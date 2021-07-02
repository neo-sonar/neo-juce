namespace mc::modulation
{

ModulatorMacro::ModulatorMacro(juce::ValueTree valueTree, juce::UndoManager* undoManager)
    : Modulator {std::move(valueTree), undoManager}, gain_ {state, ModulatorMacroIDs::gain, undoManager, 1.0f}
{
    jassert(state.hasType(ModulatorMacroIDs::type));
}

auto ModulatorMacro::getName() const -> juce::String { return "Macro"; }

auto ModulatorMacro::prepare(double sampleRate, int maxSamplesPerBlock) -> void
{
    juce::ignoreUnused(sampleRate, maxSamplesPerBlock);
}

auto ModulatorMacro::process(juce::AudioBuffer<float>& buffer) -> void
{
    jassert(buffer.getNumChannels() == 1);

    auto const gain    = static_cast<float>(gain_.get());
    auto* const output = buffer.getWritePointer(0);
    for (auto i = 0; i < buffer.getNumSamples(); ++i) { output[i] = gain; }
}

auto ModulatorMacro::reset() -> void { }

auto ModulatorMacro::setGain(float newGain) -> void { gain_ = newGain; }

auto ModulatorMacro::getGain() const -> float { return gain_.get(); }

}  // namespace mc::modulation