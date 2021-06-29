#pragma once

namespace mc
{
struct ModulationMatrix
{
    ModulationMatrix(juce::ValueTree valueTree, juce::UndoManager* undoManager);

    [[nodiscard]] auto getValueTree() -> juce::ValueTree&;
    [[nodiscard]] auto getUndoManager() -> juce::ValueTree&;

private:
    juce::ValueTree valueTree_;
    juce::UndoManager* undoManager_;
};
}  // namespace mc