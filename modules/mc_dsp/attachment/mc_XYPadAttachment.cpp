namespace mc
{

XYPadAttachment::XYPadAttachment(juce::RangedAudioParameter& parameterX, juce::RangedAudioParameter& parameterY,
                                 XYPad& pad, juce::UndoManager* um)
    : pad_ {pad}
    , attachmentX_ {parameterX, [this](float val) { setPosition(val, true); }, um}
    , attachmentY_ {parameterY, [this](float val) { setPosition(val, false); }, um}
{
    sendInitialUpdate();
    pad_.addListener(this);
}

XYPadAttachment::~XYPadAttachment()
{
    sendInitialUpdate();
    pad_.removeListener(this);
}

auto XYPadAttachment::sendInitialUpdate() -> void
{
    attachmentX_.sendInitialUpdate();
    attachmentY_.sendInitialUpdate();
}

auto XYPadAttachment::xyPadChanged(XYPad* source, juce::Point<float> position) -> void
{
    jassert(source == &pad_);
    if (ignoreCallbacks_) { return; }
    if (lastPosition_.x != position.x) { attachmentX_.setValueAsCompleteGesture(position.x); }
    if (lastPosition_.y != position.y) { attachmentY_.setValueAsCompleteGesture(position.y); }
    lastPosition_ = position;
}

auto XYPadAttachment::setPosition(float newValue, bool isX) -> void
{
    auto const svs = juce::ScopedValueSetter<bool> {ignoreCallbacks_, true};
    if (isX) { pad_.setXPosition(newValue); }
    if (!isX) { pad_.setYPosition(newValue); }
}

}  // namespace mc
