#ifndef MODERN_CIRCUITS_JUCE_MODULES_MODULATOR_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_MODULATOR_HPP

namespace mc
{

class Modulator
{
public:
    Modulator(juce::ValueTree valueTree, juce::UndoManager* undoManager = nullptr)
        : valueTree_ {std::move(valueTree)}, undoManager_ {undoManager}
    {
    }

    virtual ~Modulator() = default;

    [[nodiscard]] virtual auto getName() const -> juce::String                                        = 0;
    virtual auto prepareToPlay(double sampleRate, int maxSamplesPerBlock) -> void                     = 0;
    virtual auto processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiBuffer) -> void = 0;
    virtual auto releaseResources() -> void                                                           = 0;

    [[nodiscard]] virtual auto getValueTree() -> juce::ValueTree& { return valueTree_; }
    [[nodiscard]] virtual auto getUndoManager() const -> juce::UndoManager* { return undoManager_; }

private:
    juce::ValueTree valueTree_;
    juce::UndoManager* undoManager_;
};
}  // namespace mc

#endif  // MODERN_CIRCUITS_JUCE_MODULES_MODULATOR_HPP
