#pragma once

namespace mc::modulation
{

struct Modulator
{
    explicit Modulator(juce::ValueTree valueTree, juce::UndoManager* undoManager = nullptr);
    virtual ~Modulator() = default;

    virtual auto prepare(double sampleRate, int maxSamplesPerBlock) -> void;
    virtual auto process(juce::AudioBuffer<float>& buffer) -> void;
    virtual auto reset() -> void;

    [[nodiscard]] virtual auto getName() const -> juce::String;
    [[nodiscard]] auto getUndoManager() const -> juce::UndoManager*;

    auto setPlayHead(juce::AudioPlayHead* playHead) -> void;
    [[nodiscard]] auto getPlayHead() const noexcept -> juce::AudioPlayHead*;

    juce::ValueTree state;

private:
    juce::UndoManager* undoManager_;
    juce::AudioPlayHead* playHead_ = nullptr;
};

/// \brief An iterable list of Modulator[s].
struct ModulatorList : ValueTreeObjectListV2<Modulator>
// , private juce::AsyncUpdater
{
    /// \brief Creates a ModulatorList for a parent state.
    explicit ModulatorList(const juce::ValueTree& parent);

    /// \brief Destructor.
    ~ModulatorList() override;

    /// \internal
    [[nodiscard]] auto isSuitableType(const juce::ValueTree& /*v*/) const -> bool override;
    /// \internal
    auto createNewObject(const juce::ValueTree& /*v*/) -> Modulator* override;
    /// \internal
    void deleteObject(Modulator* t) override;
    /// \internal
    void newObjectAdded(Modulator* t) override;
    /// \internal
    void objectRemoved(Modulator* /*unused*/) override;
    /// \internal
    void objectOrderChanged() override;

private:
    // void handleAsyncUpdate() override;

    JUCE_LEAK_DETECTOR(ModulatorList)  // NOLINT
};

}  // namespace mc::modulation
