#ifndef MODERN_CIRCUITS_JUCE_MODULES_MODULATOR_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_MODULATOR_HPP

namespace mc
{

class Modulator
{
public:
    explicit Modulator(juce::ValueTree valueTree, juce::UndoManager* undoManager = nullptr)
        : valueTree_ {std::move(valueTree)}, undoManager_ {undoManager}
    {
    }

    virtual ~Modulator() = default;

    [[nodiscard]] virtual auto getName() const -> juce::String { return {}; }

    virtual auto prepareToPlay(double sampleRate, int maxSamplesPerBlock) -> void
    {
        juce::ignoreUnused(sampleRate, maxSamplesPerBlock);
    }

    virtual auto processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiBuffer) -> void
    {
        juce::ignoreUnused(buffer, midiBuffer);
    }

    virtual auto releaseResources() -> void { }

    [[nodiscard]] auto getValueTree() -> juce::ValueTree& { return valueTree_; }
    [[nodiscard]] auto getUndoManager() const -> juce::UndoManager* { return undoManager_; }

    auto setPlayHead(juce::AudioPlayHead* playHead) -> void { playHead_ = playHead; }
    [[nodiscard]] auto getPlayHead() const noexcept -> juce::AudioPlayHead* { return playHead_; }

private:
    juce::ValueTree valueTree_;
    juce::UndoManager* undoManager_;
    juce::AudioPlayHead* playHead_ = nullptr;
};
}  // namespace mc

#endif  // MODERN_CIRCUITS_JUCE_MODULES_MODULATOR_HPP
