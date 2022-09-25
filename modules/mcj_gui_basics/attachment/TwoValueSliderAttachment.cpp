namespace mc {

TwoValueSliderAttachment::TwoValueSliderAttachment(juce::ValueTree const& state,
    juce::Identifier const& idMin,
    juce::Identifier const& idMax,
    juce::Slider& slider,
    juce::UndoManager* undoManager)
    : _slider { slider }
    , _minValue { slider.getMinValueObject() }
    , _minAttachment { state, idMin, [this](auto f) { setMinValue(f); }, undoManager }
    , _maxValue { slider.getMaxValueObject() }
    , _maxAttachment { state, idMax, [this](auto f) { setMaxValue(f); }, undoManager }
{
    sendInitialUpdate();
    _slider.valueChanged();
    _slider.addListener(this);
    _minValue.addListener(this);
    _maxValue.addListener(this);
}

TwoValueSliderAttachment::~TwoValueSliderAttachment()
{
    _minValue.removeListener(this);
    _maxValue.removeListener(this);
    _slider.removeListener(this);
}

void TwoValueSliderAttachment::sendInitialUpdate()
{
    _minAttachment.sendInitialUpdate();
    _maxAttachment.sendInitialUpdate();
}

void TwoValueSliderAttachment::setMinValue(float newValue)
{
    juce::ScopedValueSetter<bool> const svs { _ignoreCallbacksMin, true };
    _slider.setMinValue(newValue, juce::sendNotificationSync, true);
}

void TwoValueSliderAttachment::setMaxValue(float newValue)
{
    juce::ScopedValueSetter<bool> const svs { _ignoreCallbacksMax, true };
    _slider.setMaxValue(newValue, juce::sendNotificationSync, true);
}

auto TwoValueSliderAttachment::valueChanged(juce::Value& v) -> void
{
    if (v.refersToSameSourceAs(_minValue)) {
        if (_ignoreCallbacksMin) { return; }
        _minAttachment.setValueAsPartOfGesture(static_cast<float>(_slider.getMinValue()));
    }

    if (v.refersToSameSourceAs(_maxValue)) {
        if (_ignoreCallbacksMax) { return; }
        _maxAttachment.setValueAsPartOfGesture(static_cast<float>(_slider.getMaxValue()));
    }
}

void TwoValueSliderAttachment::sliderValueChanged(juce::Slider* /*slider*/) { }

void TwoValueSliderAttachment::sliderDragStarted(juce::Slider* /*slider*/)
{
    _minAttachment.beginGesture();
    _maxAttachment.beginGesture();
}

void TwoValueSliderAttachment::sliderDragEnded(juce::Slider* /*slider*/)
{
    _minAttachment.endGesture();
    _maxAttachment.endGesture();
}
} // namespace mc
