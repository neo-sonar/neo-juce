#pragma once

namespace mc {

struct ValueTreeObject {
    explicit ValueTreeObject(juce::ValueTree tree, juce::UndoManager* um = nullptr);

    [[nodiscard]] auto valueTree() -> juce::ValueTree& { return _valueTree; }

    [[nodiscard]] auto valueTree() const -> juce::ValueTree const& { return _valueTree; }

    [[nodiscard]] auto undoManager() const -> juce::UndoManager* { return _undoManager; }

private:
    juce::ValueTree _valueTree;
    juce::UndoManager* _undoManager;
};

inline ValueTreeObject::ValueTreeObject(juce::ValueTree valueTree, juce::UndoManager* um)
    : _valueTree { std::move(valueTree) }, _undoManager { um }
{
}

} // namespace mc
