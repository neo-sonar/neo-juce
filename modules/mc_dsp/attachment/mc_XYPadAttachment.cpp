namespace mc {

XYPadAttachment::XYPadAttachment(juce::RangedAudioParameter& parameterX, juce::RangedAudioParameter& parameterY,
    XYPad& pad, juce::UndoManager* um)
    : pad_ { pad }
    , attachmentX_ { parameterX, [this](float val) { setPosition(val, true); }, um }
    , attachmentY_ { parameterY, [this](float val) { setPosition(val, false); }, um }
{
    pad_.setXRange(parameterX.getNormalisableRange());
    pad_.setYRange(parameterY.getNormalisableRange());
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

auto XYPadAttachment::xypadChanged(XYPad* pad, juce::Point<float> position) -> void
{
    juce::ignoreUnused(pad);
    jassert(pad == &pad_);

    if (ignoreCallbacks_) {
        return;
    }

    if (isDragging_) {
        if (lastPosition_.x != position.x) {
            attachmentX_.setValueAsPartOfGesture(position.x);
        }
        if (lastPosition_.y != position.y) {
            attachmentY_.setValueAsPartOfGesture(position.y);
        }
    } else {
        if (lastPosition_.x != position.x) {
            attachmentX_.setValueAsCompleteGesture(position.x);
        }
        if (lastPosition_.y != position.y) {
            attachmentY_.setValueAsCompleteGesture(position.y);
        }
    }

    lastPosition_ = position;
}

auto XYPadAttachment::xypadDragStarted(XYPad* pad) -> void
{
    juce::ignoreUnused(pad);
    if (!isDragging_) {
        attachmentX_.beginGesture();
        attachmentY_.beginGesture();
        isDragging_ = true;
    }
}
auto XYPadAttachment::xypadDragEnded(XYPad* pad) -> void
{
    juce::ignoreUnused(pad);
    if (isDragging_) {
        attachmentX_.endGesture();
        attachmentY_.endGesture();
        isDragging_ = false;
    }
}

auto XYPadAttachment::setPosition(float newValue, bool isX) -> void
{
    auto const svs = juce::ScopedValueSetter<bool> { ignoreCallbacks_, true };
    if (isX) {
        pad_.setValueX(newValue);
    }
    if (!isX) {
        pad_.setValueY(newValue);
    }
}

} // namespace mc
