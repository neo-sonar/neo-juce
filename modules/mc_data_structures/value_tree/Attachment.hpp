#include <utility>

#ifndef MODERN_CIRCUITS_PLUGINS_ATTACHMENT_HPP
    #define MODERN_CIRCUITS_PLUGINS_ATTACHMENT_HPP

namespace mc {

template <typename T>
struct ValueTreeAttachment : private juce::ValueTree::Listener, private juce::AsyncUpdater {
    using value_type = T;

    ValueTreeAttachment(juce::ValueTree state,
        juce::Identifier id,
        std::function<void(value_type)> parameterChangedCallback,
        juce::UndoManager* undoManager = nullptr)
        : _state { std::move(state) }
        , _id { std::move(id) }
        , _undoManager(undoManager)
        , _setValue(std::move(parameterChangedCallback))
    {
        jassert(_state.isValid());
        _state.addListener(this);
    }

    ~ValueTreeAttachment() override
    {
        _state.removeListener(this);
        cancelPendingUpdate();
    }

    void sendInitialUpdate() { valueTreePropertyChanged(_state, _id); }

    void setValueAsCompleteGesture(value_type value)
    {
        callIfValueChanged(value, [this](value_type f) {
            beginGesture();
            _state.setProperty(_id, f, _undoManager);
            endGesture();
        });
    }

    void beginGesture()
    {
        if (_undoManager != nullptr) { _undoManager->beginNewTransaction(); }
    }

    void setValueAsPartOfGesture(value_type value)
    {
        callIfValueChanged(value, [this](value_type f) { _state.setProperty(_id, f, _undoManager); });
    }

    void endGesture()
    {
        if (_undoManager != nullptr) { _undoManager->beginNewTransaction(); }
    }

private:
    MC_NODISCARD auto getValue() const -> value_type { return _state[_id]; }

    template <typename Callback>
    void callIfValueChanged(value_type newValue, Callback&& callback)
    {
        if (getValue() != newValue) { callback(newValue); }
    }

    void valueTreePropertyChanged(juce::ValueTree& tree, juce::Identifier const& property) override
    {
        if (property == _id) {
            _lastValue = juce::VariantConverter<value_type>::fromVar(tree[property]);
            if (juce::MessageManager::getInstance()->isThisTheMessageThread()) {
                cancelPendingUpdate();
                handleAsyncUpdate();
            } else {
                triggerAsyncUpdate();
            }
        }
    }

    void handleAsyncUpdate() override
    {
        if (_setValue != nullptr) { _setValue(_lastValue); }
    }

    juce::ValueTree _state;
    juce::Identifier _id;
    value_type _lastValue;
    juce::UndoManager* _undoManager;
    std::function<void(value_type)> _setValue;

    JUCE_LEAK_DETECTOR(ValueTreeAttachment) // NOLINT
};

} // namespace mc

#endif // MODERN_CIRCUITS_PLUGINS_ATTACHMENT_HPP
