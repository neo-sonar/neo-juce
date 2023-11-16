namespace neo {

ToggleButtonAttachment::ToggleButtonAttachment(juce::ValueTree state,
    juce::Identifier const& id,
    juce::Button& btn,
    juce::UndoManager* um)
    : _button { btn }, _attachment { std::move(state), id, [this](bool val) { setToggleState(val); }, um }
{
    sendInitialUpdate();
    _button.setClickingTogglesState(true);
    _button.onStateChange = [this] {
        if (_ignoreCallbacks) { return; }
        _attachment.setValueAsPartOfGesture(_button.getToggleState());
    };
}

void ToggleButtonAttachment::sendInitialUpdate() { _attachment.sendInitialUpdate(); }

void ToggleButtonAttachment::setToggleState(bool newToggleState)
{
    juce::ScopedValueSetter<bool> const svs { _ignoreCallbacks, true };
    _button.setToggleState(newToggleState, juce::sendNotificationSync);
}

} // namespace neo
