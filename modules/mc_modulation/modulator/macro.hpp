#ifndef MODERN_CIRCUITS_JUCE_MODULES_MODULATOR_MACRO_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_MODULATOR_MACRO_HPP

namespace mc
{
struct ModulatorMacroIDs
{
    inline static const juce::Identifier type = "MACRO";
    inline static const juce::Identifier gain = "gain";
};

class ModulatorMacro final : public Modulator
{
public:
    explicit ModulatorMacro(juce::ValueTree valueTree, juce::UndoManager* undoManager = nullptr);
    ~ModulatorMacro() = default;

    [[nodiscard]] auto getName() const -> juce::String override;
    auto prepareToPlay(double sampleRate, int maxSamplesPerBlock) -> void override;
    auto processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiBuffer) -> void override;
    auto releaseResources() -> void override;

    auto setGain(float newGain) -> void;
    [[nodiscard]] auto getGain() const -> float;

private:
    CachedAtomicFloat gain_;
};

}  // namespace mc

#endif  // MODERN_CIRCUITS_JUCE_MODULES_MODULATOR_MACRO_HPP
