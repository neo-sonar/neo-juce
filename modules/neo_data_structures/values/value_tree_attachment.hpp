#pragma once

namespace neo {

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
    [[nodiscard]] auto getValue() const -> value_type { return _state[_id]; }

    template <typename Callback>
    void callIfValueChanged(value_type newValue, Callback&& callback)
    {
        if (not juce::exactlyEqual(getValue(), newValue)) { callback(newValue); }
    }

    void valueTreePropertyChanged(juce::ValueTree& tree, juce::Identifier const& property) override
    {
        if (property == _id) {
            _lastValue = fromVar<value_type>(tree[property]);
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

} // namespace neo
