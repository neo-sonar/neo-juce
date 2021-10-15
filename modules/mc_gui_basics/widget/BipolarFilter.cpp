namespace mc {

BipolarFilter::BipolarFilter(juce::String const& name) : juce::Component { name } { }

auto BipolarFilter::setValue(double newValue) -> void
{
    currentValue_ = range_.clipValue(newValue);
    repaint();
    listeners_.call([this](Listener& listener) { listener.bipolarFilterValueChanged(this); });
}

auto BipolarFilter::getValue() const noexcept -> double { return currentValue_; }

auto BipolarFilter::setDoubleClickReturnValue(bool shouldDoubleClickBeEnabled, double valueToSetOnDoubleClick) -> void
{
    doubleClickToResetIsEnabled_ = shouldDoubleClickBeEnabled;
    defaultValue_                = valueToSetOnDoubleClick;
}

auto BipolarFilter::getDoubleClickReturnValue() const noexcept -> double { return defaultValue_; }

auto BipolarFilter::isDoubleClickReturnEnabled() const noexcept -> bool { return doubleClickToResetIsEnabled_; }

auto BipolarFilter::paint(juce::Graphics& g) -> void
{
    auto area = getLocalBounds().toFloat();
    g.fillAll(juce::Colours::white);

    area = area.reduced(area.getWidth() / 15.0f);

    auto thumbX     = juce::jmap<float>(static_cast<float>(currentValue_), -1.0f, 1.0f, area.getX(), area.getRight());
    auto thumbY     = area.getY() + (area.getHeight() / 10.0f) * 3.5f;
    auto thumbWidth = std::min(area.getWidth() / 5.0f, area.getHeight() / 5.0f);
    thumbArea_      = juce::Rectangle<float> { 0.0f, 0.0f, thumbWidth, thumbWidth }.withCentre({ thumbX, thumbY });

    g.setColour(juce::Colours::blue);
    g.drawLine({ thumbArea_.getCentre(), area.getBottomLeft() }, 3.0f);
    g.drawLine({ thumbArea_.getCentre(), area.getBottomRight() }, 3.0f);

    g.setColour(juce::Colours::green);
    g.fillEllipse(thumbArea_);
}

auto BipolarFilter::addListener(Listener* const listener) -> void { listeners_.add(listener); }

auto BipolarFilter::removeListener(Listener* const listener) -> void { listeners_.remove(listener); }

auto BipolarFilter::resized() -> void { }

auto BipolarFilter::mouseDown(juce::MouseEvent const& mouseEvent) -> void
{
    if (MouseEventUtils::hitTest(mouseEvent, thumbArea_)) { startDragging(); }
}

auto BipolarFilter::mouseDrag(juce::MouseEvent const& mouseEvent) -> void
{
    if (isDragging_) {
        auto const left     = static_cast<double>(getLocalBounds().getX());
        auto const right    = static_cast<double>(getLocalBounds().getRight());
        auto const screenX  = static_cast<double>(mouseEvent.position.x);
        auto const newValue = juce::jmap<double>(screenX, left, right, range_.getStart(), range_.getEnd());
        setValue(newValue);
    }
}

auto BipolarFilter::mouseUp(juce::MouseEvent const& mouseEvent) -> void
{
    juce::ignoreUnused(mouseEvent);
    stopDragging();
}

auto BipolarFilter::startDragging() -> void
{
    isDragging_ = true;
    listeners_.call([this](Listener& listener) { listener.bipolarFilterDragStarted(this); });
}

auto BipolarFilter::stopDragging() -> void
{
    if (isDragging_) {
        isDragging_ = false;
        listeners_.call([this](Listener& listener) { listener.bipolarFilterDragEnded(this); });
    }
}

} // namespace mc