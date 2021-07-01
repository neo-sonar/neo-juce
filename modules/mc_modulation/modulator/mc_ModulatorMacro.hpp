#pragma once
namespace mc::modulation
{
struct ModulatorMacroIDs
{
    inline static const juce::Identifier type = "MACRO";
    inline static const juce::Identifier gain = "gain";
};

struct ModulatorMacro final : Modulator
{
    explicit ModulatorMacro(juce::ValueTree valueTree, juce::UndoManager* undoManager = nullptr);
    ~ModulatorMacro() override = default;

    ModulatorMacro(const ModulatorMacro& other) = delete;
    ModulatorMacro(ModulatorMacro&& other)      = delete;
    auto operator=(const ModulatorMacro& rhs) -> ModulatorMacro& = delete;
    auto operator=(ModulatorMacro&& rhs) -> ModulatorMacro& = delete;

    [[nodiscard]] auto getName() const -> juce::String override;
    auto prepare(double sampleRate, int maxSamplesPerBlock) -> void override;
    auto process(juce::AudioBuffer<float>& buffer) -> void override;
    auto reset() -> void override;

    auto setGain(float newGain) -> void;
    [[nodiscard]] auto getGain() const -> float;

private:
    CachedAtomicFloat gain_;
};

}  // namespace mc::modulation
