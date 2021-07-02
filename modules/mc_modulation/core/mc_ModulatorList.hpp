#pragma once

namespace mc::modulation
{

/// \brief An iterable list of Modulator[s].
struct ModulatorList : ValueTreeObjectListV2<Modulator>
{
    /// \brief Creates a ModulatorList for a parent state.
    explicit ModulatorList(juce::ValueTree const& parent, juce::UndoManager* undoManager = nullptr);

    /// \brief Destructor.
    ~ModulatorList() override;

    /// \brief Returns a Modulator for a given state.
    [[nodiscard]] auto getModulatorFor(juce::ValueTree const& state) const -> Modulator*;

    /// \internal
    [[nodiscard]] auto isSuitableType(juce::ValueTree const& v) const -> bool override;
    /// \internal
    auto createNewObject(juce::ValueTree const& v) -> Modulator* override;
    /// \internal
    auto deleteObject(Modulator* m) -> void override;
    /// \internal
    auto newObjectAdded(Modulator* m) -> void override;
    /// \internal
    auto objectRemoved(Modulator* m) -> void override;
    /// \internal
    auto objectOrderChanged() -> void override;

private:
    juce::UndoManager* undoManager_ {nullptr};
    Modulator::Array modulators_ {};

    JUCE_LEAK_DETECTOR(ModulatorList)  // NOLINT
};

}  // namespace mc::modulation