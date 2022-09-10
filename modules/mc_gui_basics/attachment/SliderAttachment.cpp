namespace mc {

SliderValueTreeAttachment::SliderValueTreeAttachment(juce::ValueTree state,
    juce::Identifier const& id,
    juce::Slider& slider,
    juce::UndoManager* undoManager)
    : slider_ { slider }, attachment_ { std::move(state), id, [this](auto f) { setValue(f); }, undoManager }
{
    sendInitialUpdate();
    slider_.valueChanged();
    slider_.addListener(this);
}

SliderValueTreeAttachment::~SliderValueTreeAttachment() { slider_.removeListener(this); }

void SliderValueTreeAttachment::sendInitialUpdate() { attachment_.sendInitialUpdate(); }

void SliderValueTreeAttachment::setValue(float newValue)
{
    juce::ScopedValueSetter<bool> svs(ignoreCallbacks_, true);
    slider_.setValue(newValue, juce::sendNotificationSync);
}
void SliderValueTreeAttachment::sliderValueChanged(juce::Slider* /*slider*/)
{
    if (ignoreCallbacks_ || juce::ModifierKeys::currentModifiers.isRightButtonDown()) { return; }
    attachment_.setValueAsPartOfGesture(static_cast<float>(slider_.getValue()));
}

void SliderValueTreeAttachment::sliderDragStarted(juce::Slider* /*slider*/) { attachment_.beginGesture(); }
void SliderValueTreeAttachment::sliderDragEnded(juce::Slider* /*slider*/) { attachment_.endGesture(); }

} // namespace mc
