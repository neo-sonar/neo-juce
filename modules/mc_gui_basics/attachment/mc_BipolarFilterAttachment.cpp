namespace mc {
BipolarFilterValueTreeAttachment::BipolarFilterValueTreeAttachment(
    juce::ValueTree state, juce::Identifier const& id, BipolarFilter& slider, juce::UndoManager* undoManager)
    : slider_ { slider }, attachment_ { std::move(state), id, [this](auto f) { setValue(f); }, undoManager }
{
    sendInitialUpdate();
    //    slider_.valueChanged();
    slider_.addListener(this);
}

BipolarFilterValueTreeAttachment::~BipolarFilterValueTreeAttachment() { slider_.removeListener(this); }

void BipolarFilterValueTreeAttachment::sendInitialUpdate() { attachment_.sendInitialUpdate(); }

void BipolarFilterValueTreeAttachment::setValue(float newValue)
{
    juce::ScopedValueSetter<bool> svs(ignoreCallbacks_, true);
    slider_.setValue(newValue);
    //    slider_.setValue(newValue, juce::sendNotificationSync);
}
void BipolarFilterValueTreeAttachment::bipolarFilterValueChanged(BipolarFilter* /*slider*/)
{
    if (ignoreCallbacks_ || juce::ModifierKeys::currentModifiers.isRightButtonDown()) { return; }
    attachment_.setValueAsPartOfGesture(static_cast<float>(slider_.getValue()));
}

void BipolarFilterValueTreeAttachment::bipolarFilterDragStarted(BipolarFilter* /*slider*/)
{
    attachment_.beginGesture();
}
void BipolarFilterValueTreeAttachment::bipolarFilterDragEnded(BipolarFilter* /*slider*/) { attachment_.endGesture(); }
} // namespace mc