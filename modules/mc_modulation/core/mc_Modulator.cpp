namespace mc::modulation
{

Modulator::Modulator(juce::ValueTree valueTree, juce::UndoManager* undoManager)
    : state {std::move(valueTree)}, undoManager_ {undoManager}
{
    color_.referTo(state, "color", undoManager_, juce::Colour {});
}

auto Modulator::getName() const -> juce::String { return {}; }

auto Modulator::prepare(double sampleRate, int maxSamplesPerBlock) -> void
{
    juce::ignoreUnused(sampleRate, maxSamplesPerBlock);
}

auto Modulator::process(juce::AudioBuffer<float>& buffer) -> void { juce::ignoreUnused(buffer); }

auto Modulator::reset() -> void { }

auto Modulator::setColour(juce::Colour newColor) -> void { color_ = newColor; }

auto Modulator::getColour() const -> juce::Colour { return color_; }

}  // namespace mc::modulation
