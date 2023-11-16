namespace neo {

XYPadAttachment::XYPadAttachment(juce::RangedAudioParameter& parameterX,
    juce::RangedAudioParameter& parameterY,
    XYPad& pad,
    juce::UndoManager* um)
    : _pad { pad }
    , _attachmentX { parameterX, [this](float val) { setPosition(val, true); }, um }
    , _attachmentY { parameterY, [this](float val) { setPosition(val, false); }, um }
{
    _pad.setXRange(parameterX.getNormalisableRange());
    _pad.setYRange(parameterY.getNormalisableRange());
    sendInitialUpdate();
    _pad.addListener(this);
}

XYPadAttachment::~XYPadAttachment()
{
    sendInitialUpdate();
    _pad.removeListener(this);
}

auto XYPadAttachment::sendInitialUpdate() -> void
{
    _attachmentX.sendInitialUpdate();
    _attachmentY.sendInitialUpdate();
}

auto XYPadAttachment::xypadChanged(XYPad* pad, juce::Point<float> position) -> void
{
    juce::ignoreUnused(pad);
    jassert(pad == &_pad);

    if (_ignoreCallbacks) { return; }

    if (_isDragging) {
        if (not juce::exactlyEqual(_lastPosition.x, position.x)) { _attachmentX.setValueAsPartOfGesture(position.x); }
        if (not juce::exactlyEqual(_lastPosition.y, position.y)) { _attachmentY.setValueAsPartOfGesture(position.y); }
    } else {
        if (not juce::exactlyEqual(_lastPosition.x, position.x)) { _attachmentX.setValueAsCompleteGesture(position.x); }
        if (not juce::exactlyEqual(_lastPosition.y, position.y)) { _attachmentY.setValueAsCompleteGesture(position.y); }
    }

    _lastPosition = position;
}

auto XYPadAttachment::xypadDragStarted(XYPad* pad) -> void
{
    juce::ignoreUnused(pad);
    if (!_isDragging) {
        _attachmentX.beginGesture();
        _attachmentY.beginGesture();
        _isDragging = true;
    }
}
auto XYPadAttachment::xypadDragEnded(XYPad* pad) -> void
{
    juce::ignoreUnused(pad);
    if (_isDragging) {
        _attachmentX.endGesture();
        _attachmentY.endGesture();
        _isDragging = false;
    }
}

auto XYPadAttachment::setPosition(float newValue, bool isX) -> void
{
    juce::ScopedValueSetter<bool> const svs { _ignoreCallbacks, true };
    if (isX) { _pad.setValueX(newValue); }
    if (!isX) { _pad.setValueY(newValue); }
}

} // namespace neo
