namespace mc {

SliderValueTreeAttachment::SliderValueTreeAttachment(juce::ValueTree state,
    juce::Identifier const& id,
    juce::Slider& slider,
    juce::UndoManager* undoManager)
    : _slider { slider }, _attachment { std::move(state), id, [this](auto f) { setValue(f); }, undoManager }
{
    sendInitialUpdate();
    _slider.valueChanged();
    _slider.addListener(this);
}

SliderValueTreeAttachment::~SliderValueTreeAttachment() { _slider.removeListener(this); }

void SliderValueTreeAttachment::sendInitialUpdate() { _attachment.sendInitialUpdate(); }

void SliderValueTreeAttachment::setValue(float newValue)
{
    juce::ScopedValueSetter<bool> svs(_ignoreCallbacks, true);
    _slider.setValue(newValue, juce::sendNotificationSync);
}
void SliderValueTreeAttachment::sliderValueChanged(juce::Slider* /*slider*/)
{
    if (_ignoreCallbacks || juce::ModifierKeys::currentModifiers.isRightButtonDown()) { return; }
    _attachment.setValueAsPartOfGesture(static_cast<float>(_slider.getValue()));
}

void SliderValueTreeAttachment::sliderDragStarted(juce::Slider* /*slider*/) { _attachment.beginGesture(); }
void SliderValueTreeAttachment::sliderDragEnded(juce::Slider* /*slider*/) { _attachment.endGesture(); }

} // namespace mc
