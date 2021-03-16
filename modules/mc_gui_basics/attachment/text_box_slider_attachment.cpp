namespace mc
{
TextBoxSliderValueTreeAttachment::TextBoxSliderValueTreeAttachment(juce::ValueTree state, juce::Identifier const& id,
                                                                   TextBoxSlider& slider,
                                                                   juce::UndoManager* undoManager)
    : slider_ {slider}, attachment_ {std::move(state), id, [this](auto f) { setValue(f); }, undoManager}
{
    sendInitialUpdate();
    //    slider_.valueChanged();
    slider_.addListener(this);
}

TextBoxSliderValueTreeAttachment::~TextBoxSliderValueTreeAttachment() { slider_.removeListener(this); }

void TextBoxSliderValueTreeAttachment::sendInitialUpdate() { attachment_.sendInitialUpdate(); }

void TextBoxSliderValueTreeAttachment::setValue(float newValue)
{
    juce::ScopedValueSetter<bool> svs(ignoreCallbacks_, true);
    slider_.setValue(newValue, juce::sendNotificationSync);
}
void TextBoxSliderValueTreeAttachment::textBoxSliderValueChanged(TextBoxSlider* /*slider*/)
{
    if (ignoreCallbacks_ || juce::ModifierKeys::currentModifiers.isRightButtonDown()) { return; }
    attachment_.setValueAsPartOfGesture(static_cast<float>(slider_.getValue()));
}

void TextBoxSliderValueTreeAttachment::textBoxSliderDragStarted(TextBoxSlider* /*slider*/)
{
    attachment_.beginGesture();
}
void TextBoxSliderValueTreeAttachment::textBoxSliderDragEnded(TextBoxSlider* /*slider*/) { attachment_.endGesture(); }
}  // namespace mc