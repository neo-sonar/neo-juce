#ifndef MODERN_CIRCUITS_JUCE_MODULES_MODULATOR_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_MODULATOR_HPP

namespace mc
{

struct Modulator
{
    explicit Modulator(juce::ValueTree valueTree, juce::UndoManager* undoManager = nullptr);
    virtual ~Modulator() = default;

    virtual auto prepare(double sampleRate, int maxSamplesPerBlock) -> void;
    virtual auto process(juce::AudioBuffer<float>& buffer) -> void;
    virtual auto reset() -> void;

    [[nodiscard]] virtual auto getName() const -> juce::String;
    [[nodiscard]] auto getValueTree() -> juce::ValueTree&;
    [[nodiscard]] auto getUndoManager() const -> juce::UndoManager*;

    auto setPlayHead(juce::AudioPlayHead* playHead) -> void;
    [[nodiscard]] auto getPlayHead() const noexcept -> juce::AudioPlayHead*;

private:
    juce::ValueTree valueTree_;
    juce::UndoManager* undoManager_;
    juce::AudioPlayHead* playHead_ = nullptr;
};
}  // namespace mc

#endif  // MODERN_CIRCUITS_JUCE_MODULES_MODULATOR_HPP
