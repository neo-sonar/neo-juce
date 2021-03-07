#ifndef MC_JUCE_BUNDLE_VALUE_TREE_UTILS_HPP
#define MC_JUCE_BUNDLE_VALUE_TREE_UTILS_HPP

namespace mc
{
template<typename ItemType>
class ValueTreeObject
{
public:
    ValueTreeObject(juce::ValueTree state, juce::UndoManager* undoManager) : state_ {state}, undoManager_ {undoManager}
    {
    }

    [[nodiscard]] auto getValueTree() const -> juce::ValueTree const& { return state_; }
    [[nodiscard]] auto getValueTree() -> juce::ValueTree& { return state_; }
    [[nodiscard]] auto getUndoManager() -> juce::UndoManager* { return undoManager_; }

private:
    juce::ValueTree state_;
    juce::UndoManager* undoManager_;
};

}  // namespace mc
#endif  // MC_JUCE_BUNDLE_VALUE_TREE_UTILS_HPP