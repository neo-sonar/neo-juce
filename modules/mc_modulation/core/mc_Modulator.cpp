namespace mc
{

Modulator::Modulator(juce::ValueTree valueTree, juce::UndoManager* undoManager)
    : valueTree_ {std::move(valueTree)}, undoManager_ {undoManager}
{
}

auto Modulator::getName() const -> juce::String { return {}; }

auto Modulator::prepare(double sampleRate, int maxSamplesPerBlock) -> void
{
    juce::ignoreUnused(sampleRate, maxSamplesPerBlock);
}

auto Modulator::process(juce::AudioBuffer<float>& buffer) -> void { juce::ignoreUnused(buffer); }

auto Modulator::reset() -> void { }

auto Modulator::getValueTree() -> juce::ValueTree& { return valueTree_; }
auto Modulator::getUndoManager() const -> juce::UndoManager* { return undoManager_; }

auto Modulator::setPlayHead(juce::AudioPlayHead* playHead) -> void { playHead_ = playHead; }
auto Modulator::getPlayHead() const noexcept -> juce::AudioPlayHead* { return playHead_; }
}  // namespace mc
