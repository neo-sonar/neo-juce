#pragma once

namespace mc::modulation
{

struct Modulator : juce::ReferenceCountedObject
{
    using Ptr   = juce::ReferenceCountedObjectPtr<Modulator>;
    using Array = juce::ReferenceCountedArray<Modulator>;

    explicit Modulator(juce::ValueTree valueTree, juce::UndoManager* undoManager = nullptr);
    virtual ~Modulator() = default;

    [[nodiscard]] virtual auto getName() const -> juce::String;

    virtual auto prepare(double sampleRate, int maxSamplesPerBlock) -> void;
    virtual auto process(juce::AudioBuffer<float>& buffer) -> void;
    virtual auto reset() -> void;

    /// \brief Sets a color for this modulator to use.
    auto setColour(juce::Colour newColor) -> void;

    /// \brief Returns the color of this modulator.
    auto getColour() const -> juce::Colour;

    juce::ValueTree state;

private:
    juce::UndoManager* undoManager_;
    juce::CachedValue<juce::Colour> color_;
};

}  // namespace mc::modulation
