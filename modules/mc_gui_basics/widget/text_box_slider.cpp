namespace mc
{

TextBoxSlider::TextBoxSlider()
{
    text_.setEditable(false, true);
    text_.setFont(juce::Font(11.0f));
    text_.setJustificationType(juce::Justification::centred);
    text_.addMouseListener(this, false);
    addAndMakeVisible(text_);
}

TextBoxSlider::TextBoxSlider(juce::String const& name) : juce::Component {name}
{
    text_.setEditable(false, true);
    text_.setFont(juce::Font(11.0f));
    text_.setJustificationType(juce::Justification::centred);
    text_.addMouseListener(this, false);
    addAndMakeVisible(text_);
}

auto TextBoxSlider::setValue(double const newValue) -> void
{
    if (auto const clipped = range_.clipValue(newValue); clipped != value_)
    {
        value_ = clipped;
        text_.setText(getTextFromValue(clipped), juce::dontSendNotification);
        listenerList_.call([self = this](auto& listener) { listener.textBoxSliderValueChanged(self); });
        if (static_cast<bool>(onValueChange)) { onValueChange(); }
    }
}

auto TextBoxSlider::getValue() const noexcept -> double { return value_; }

auto TextBoxSlider::setRange(juce::Range<double> const newRange, double const newInterval) -> void
{
    range_    = newRange;
    interval_ = newInterval;
}

auto TextBoxSlider::getRange() const noexcept -> juce::Range<double> { return range_; }

auto TextBoxSlider::getMaximum() const noexcept -> double { return range_.getEnd(); }

auto TextBoxSlider::getMinimum() const noexcept -> double { return range_.getStart(); }

auto TextBoxSlider::getInterval() const noexcept -> double { return interval_; }

auto TextBoxSlider::setDoubleClickReturnValue(bool shouldDoubleClickBeEnabled, double valueToSetOnDoubleClick) -> void
{
    doubleClickToResetIsEnabled_ = shouldDoubleClickBeEnabled;
    defaultValue_                = valueToSetOnDoubleClick;
}

auto TextBoxSlider::getDoubleClickReturnValue() const noexcept -> double { return defaultValue_; }

auto TextBoxSlider::isDoubleClickReturnEnabled() const noexcept -> bool { return doubleClickToResetIsEnabled_; }

auto TextBoxSlider::setTextBoxIsEditable(bool const shouldBeEditable) -> void { text_.setEditable(shouldBeEditable); }

auto TextBoxSlider::isTextBoxEditable() const noexcept -> bool { return text_.isEditable(); }

auto TextBoxSlider::getValueFromText(juce::String const& text) const -> double
{
    if (static_cast<bool>(valueFromText)) { return valueFromText(text); }
    return text.getFloatValue();
}

auto TextBoxSlider::getTextFromValue(double const value) const -> juce::String
{
    if (static_cast<bool>(textFromValue)) { return textFromValue(value); }
    return juce::String {value, 1};
}

auto TextBoxSlider::setJustificationType(juce::Justification const justification) -> void
{
    text_.setJustificationType(justification);
}

auto TextBoxSlider::getJustificationType() const noexcept -> juce::Justification
{
    return text_.getJustificationType();
}

auto TextBoxSlider::addListener(TextBoxSlider::Listener* const listener) -> void { listenerList_.add(listener); }

auto TextBoxSlider::removeListener(TextBoxSlider::Listener* const listener) -> void { listenerList_.remove(listener); }

auto TextBoxSlider::resized() -> void { text_.setBounds(getLocalBounds()); }

auto TextBoxSlider::mouseDrag(juce::MouseEvent const& event) -> void
{
    if (!isDragging_) { startDrag(); }
    auto const direction = event.getDistanceFromDragStartY() > 0 ? -1.0 : 1.0;
    setValue(getValue() + interval_ * direction);
}

auto TextBoxSlider::mouseUp(juce::MouseEvent const& event) -> void
{
    juce::ignoreUnused(event);
    if (isDragging_) { stopDrag(); }
}

auto TextBoxSlider::mouseDoubleClick(juce::MouseEvent const& event) -> void
{
    juce::ignoreUnused(event);
    if (doubleClickToResetIsEnabled_) { setValue(defaultValue_); }
}

auto TextBoxSlider::mouseWheelMove(juce::MouseEvent const& event, juce::MouseWheelDetails const& wheel) -> void
{
    juce::ignoreUnused(event);
    auto const delta    = wheel.deltaY < 0.0f ? interval_ * -1.0 : interval_;
    auto const newValue = getValue() + delta;
    setValue(newValue);
}

auto TextBoxSlider::startDrag() -> void
{
    isDragging_ = true;
    listenerList_.call([self = this](Listener& listener) { listener.textBoxSliderDragStarted(self); });
    if (static_cast<bool>(onDragStart)) { onDragStart(); }
}

auto TextBoxSlider::stopDrag() -> void
{
    isDragging_ = false;
    listenerList_.call([self = this](Listener& listener) { listener.textBoxSliderDragEnded(self); });
    if (static_cast<bool>(onDragEnd)) { onDragEnd(); }
}

}  // namespace mc