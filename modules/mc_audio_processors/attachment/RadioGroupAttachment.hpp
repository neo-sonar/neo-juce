#pragma once

namespace mc {

/// \brief An object of this class maintains a connection between a
/// RadioGroupAttachment and a plug-in parameter of type choice.
///
/// \details During the lifetime of this object it keeps the two things in sync,
/// making it easy to connect a selector to a parameter. When this object is deleted,
/// the connection is broken. Make sure that your parameter and Selector are not
/// deleted before this object!
template <typename ButtonType>
struct RadioGroupAttachment final : juce::Button::Listener {

    /// \brief Creates a connection between a plug-in parameter and a Slider.
    /// \param parameter     The parameter to use
    /// \param buttons       Group of buttons to be attached
    /// \param undoManager   An optional juce::UndoManager
    RadioGroupAttachment(juce::RangedAudioParameter& parameter,
        juce::OwnedArray<ButtonType>& buttons,
        juce::UndoManager* um = nullptr);

    /// \brief Destructor
    ~RadioGroupAttachment() override;

    /// \brief Call this after setting up your slider in the case where you
    /// need to do extra setup after constructing this attachment.
    void sendInitialUpdate();

private:
    void buttonClicked(juce::Button* b) override;
    void setValue(float newValue);

    juce::OwnedArray<ButtonType>& _buttons;
    juce::ParameterAttachment _attachment;
    bool _ignoreCallbacks = false;
};

template <typename ButtonType>
RadioGroupAttachment<ButtonType>::RadioGroupAttachment(juce::RangedAudioParameter& parameter,
    juce::OwnedArray<ButtonType>& buttons,
    juce::UndoManager* um)
    : _buttons { buttons }, _attachment { parameter, [this](float f) { setValue(f); }, um }
{
    auto const groupID = juce::Random::getSystemRandom().nextInt();
    for (auto* button : _buttons) {
        button->addListener(this);
        button->setRadioGroupId(groupID);
        button->setClickingTogglesState(true);
    }

    sendInitialUpdate();
}

template <typename ButtonType>
RadioGroupAttachment<ButtonType>::~RadioGroupAttachment()
{
    sendInitialUpdate();
    for (auto* button : _buttons) { button->removeListener(this); }
}

template <typename ButtonType>
void RadioGroupAttachment<ButtonType>::sendInitialUpdate()
{
    _attachment.sendInitialUpdate();
}

template <typename ButtonType>
void RadioGroupAttachment<ButtonType>::buttonClicked(juce::Button* b)
{
    if (_ignoreCallbacks) { return; }
    for (auto i = 0; i < _buttons.size(); ++i) {
        if (_buttons[i] == b && b->getToggleState()) {
            _attachment.setValueAsCompleteGesture(static_cast<float>(i));
            return;
        }
    }
}

template <typename ButtonType>
void RadioGroupAttachment<ButtonType>::setValue(float newValue)
{
    juce::ScopedValueSetter<bool> const svs { _ignoreCallbacks, true };
    _buttons[static_cast<int>(newValue)]->setToggleState(true, juce::NotificationType::sendNotificationSync);
}

} // namespace mc
