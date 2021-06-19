namespace mc
{
XYPad::XYPad() : normalizedValues_ {0.0f, 0.0f} { }

auto XYPad::paint(juce::Graphics& g) -> void
{
    if (auto* lnf = dynamic_cast<XYPad::LookAndFeelMethods*>(&getLookAndFeel()); lnf != nullptr)
    {
        lnf->drawXYPad(g, getLocalBounds(), *this);
        return;
    }

    jassertfalse;
}

auto XYPad::resized() -> void { bounds_ = getLocalBounds(); }

auto XYPad::getXPosition() const noexcept -> float { return xRange_.convertFrom0to1(normalizedValues_.x); }

auto XYPad::getYPosition() const noexcept -> float { return yRange_.convertFrom0to1(normalizedValues_.y); }

auto XYPad::getNormalisedXPosition() const noexcept -> float { return normalizedValues_.x; }

auto XYPad::getNormalisedYPosition() const noexcept -> float { return normalizedValues_.y; }

auto XYPad::setXPosition(float x) noexcept -> void { setNormalisedXPosition(xRange_.convertTo0to1(x)); }

auto XYPad::setYPosition(float y) noexcept -> void { setNormalisedYPosition(yRange_.convertTo0to1(y)); }

auto XYPad::setNormalisedXPosition(float x) noexcept -> void
{
    normalizedValues_.x = x;
    listeners_.call([this](Listener& listener) { listener.xypadChanged(this, {getXPosition(), getYPosition()}); });
    repaint();
}

auto XYPad::setNormalisedYPosition(float y) noexcept -> void
{
    normalizedValues_.y = y;
    listeners_.call([this](Listener& listener) { listener.xypadChanged(this, {getXPosition(), getYPosition()}); });
    repaint();
}

auto XYPad::getXRange() const noexcept -> juce::NormalisableRange<float> { return xRange_; }

auto XYPad::getYRange() const noexcept -> juce::NormalisableRange<float> { return yRange_; }

auto XYPad::setXRange(juce::NormalisableRange<float> const& newRange) noexcept -> void { xRange_ = newRange; }

auto XYPad::setYRange(juce::NormalisableRange<float> const& newRange) noexcept -> void { yRange_ = newRange; }

auto XYPad::mouseMove(juce::MouseEvent const& event) -> void
{
    thumbColor_ = thumbHitTest(event) ? juce::Colours::white : juce::Colours::grey;
    repaint();
}

auto XYPad::mouseDown(juce::MouseEvent const& event) -> void
{
    setXPosition(getValueFromPixel(event.x, true));
    setYPosition(getValueFromPixel(event.y, false));
    thumbColor_ = juce::Colours::white;
    repaint();
}

auto XYPad::mouseUp(juce::MouseEvent const& event) -> void
{
    juce::ignoreUnused(event);
    stopDragging();
    repaint();
}

auto XYPad::mouseDrag(juce::MouseEvent const& event) -> void
{
    if (!isDragging_) { startDragging(); }

    auto p = juce::Point<float> {};
    p.x    = std::clamp<float>(event.x, bounds_.getX(), bounds_.getRight());
    p.y    = std::clamp<float>(event.y, bounds_.getY(), bounds_.getBottom());
    setXPosition(getValueFromPixel(p.x, true));
    setYPosition(getValueFromPixel(p.y, false));

    repaint();
}

auto XYPad::getValueFromPixel(int pixel, bool isXAxis) const -> float
{
    auto const x      = static_cast<float>(bounds_.getX());
    auto const y      = static_cast<float>(bounds_.getY());
    auto const right  = static_cast<float>(bounds_.getRight());
    auto const bottom = static_cast<float>(bounds_.getBottom());

    if (isXAxis) { return juce::jmap<float>(static_cast<float>(pixel), x, right, xRange_.start, xRange_.end); }
    return juce::jmap<float>(static_cast<float>(pixel), y, bottom, yRange_.start, yRange_.end);
}

auto XYPad::getPixelFromNormalizedValue(float value, bool x) const -> int
{
    if (x) { return static_cast<int>(bounds_.getX() + (value * bounds_.getWidth())); }
    return static_cast<int>(bounds_.getY() + value * bounds_.getHeight());
}

auto XYPad::thumbHitTest(juce::MouseEvent const& event) const -> bool
{
    auto const x             = getPixelFromNormalizedValue(normalizedValues_.x, true);
    auto const y             = getPixelFromNormalizedValue(normalizedValues_.y, false);
    auto const thumb         = juce::Rectangle {0, 0, 8, 8}.withCentre({static_cast<int>(x), static_cast<int>(y)});
    auto const isInXPosition = event.x >= thumb.getX() && event.x <= thumb.getRight();
    auto const isInYPosition = event.y >= thumb.getY() && event.y <= thumb.getBottom();
    return isInXPosition && isInYPosition;
}

auto XYPad::startDragging() -> void
{
    listeners_.call([this](Listener& listener) { listener.xypadDragStarted(this); });
    isDragging_ = true;
}

auto XYPad::stopDragging() -> void
{
    isDragging_ = false;
    listeners_.call([this](Listener& listener) { listener.xypadDragEnded(this); });
}

}  // namespace mc