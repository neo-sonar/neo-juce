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

auto XYPad::getValueX() const noexcept -> float { return xRange_.convertFrom0to1(normalizedValues_.x); }

auto XYPad::getValueY() const noexcept -> float { return yRange_.convertFrom0to1(normalizedValues_.y); }

auto XYPad::getNormalizedX() const noexcept -> float { return normalizedValues_.x; }

auto XYPad::getNormalizedY() const noexcept -> float { return normalizedValues_.y; }

auto XYPad::setValueX(float x) -> void { setNormalizedX(xRange_.convertTo0to1(x)); }

auto XYPad::setValueY(float y) -> void { setNormalizedY(yRange_.convertTo0to1(y)); }

auto XYPad::setNormalizedX(float x) -> void
{
    normalizedValues_.x = x;
    listeners_.call([this](Listener& listener) { listener.xypadChanged(this, {getValueX(), getValueY()}); });
    repaint();
}

auto XYPad::setNormalizedY(float y) -> void
{
    normalizedValues_.y = y;
    listeners_.call([this](Listener& listener) { listener.xypadChanged(this, {getValueX(), getValueY()}); });
    repaint();
}

auto XYPad::getXRange() const noexcept -> juce::NormalisableRange<float> { return xRange_; }

auto XYPad::getYRange() const noexcept -> juce::NormalisableRange<float> { return yRange_; }

auto XYPad::setDirectionX(bool startShouldBeOnLeft) -> void { startShouldBeOnLeft_ = startShouldBeOnLeft; }
auto XYPad::setDirectionY(bool startShouldBeOnTop) -> void { startShouldBeOnTop_ = startShouldBeOnTop; }

auto XYPad::setXRange(juce::NormalisableRange<float> const& newRange) -> void { xRange_ = newRange; }

auto XYPad::setYRange(juce::NormalisableRange<float> const& newRange) -> void { yRange_ = newRange; }

auto XYPad::mouseMove(juce::MouseEvent const& event) -> void
{
    thumbColor_ = thumbHitTest(event) ? juce::Colours::white : juce::Colours::grey;
    repaint();
}

auto XYPad::mouseDown(juce::MouseEvent const& event) -> void
{
    setValueX(getValueFromPixel(event.x, true));
    setValueY(getValueFromPixel(event.y, false));
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

    auto p = juce::Point<int> {};
    p.x    = std::clamp<int>(event.x, bounds_.getX(), bounds_.getRight());
    p.y    = std::clamp<int>(event.y, bounds_.getY(), bounds_.getBottom());
    setValueX(getValueFromPixel(p.x, true));
    setValueY(getValueFromPixel(p.y, false));

    repaint();
}

auto XYPad::getValueFromPixel(int pixel, bool isXAxis) const -> float
{
    auto const x      = static_cast<float>(bounds_.getX());
    auto const y      = static_cast<float>(bounds_.getY());
    auto const right  = static_cast<float>(bounds_.getRight());
    auto const bottom = static_cast<float>(bounds_.getBottom());

    if (isXAxis)
    {
        auto const startX = startShouldBeOnLeft_ ? xRange_.start : xRange_.end;
        auto const endX   = startShouldBeOnLeft_ ? xRange_.end : xRange_.start;
        return juce::jmap<float>(static_cast<float>(pixel), x, right, startX, endX);
    }

    auto const startY = startShouldBeOnTop_ ? yRange_.start : yRange_.end;
    auto const endY   = startShouldBeOnTop_ ? yRange_.end : yRange_.start;
    return juce::jmap<float>(static_cast<float>(pixel), y, bottom, startY, endY);
}

auto XYPad::getPixelFromNormalizedValue(float value, bool x) const -> int
{
    if (x)
    {
        auto const direction  = startShouldBeOnLeft_ ? 1.0f : -1.0f;
        auto const start      = startShouldBeOnLeft_ ? bounds_.getX() : bounds_.getRight();
        auto const proportion = bounds_.getWidth() * value;
        return static_cast<int>(start + (proportion * direction));
    }

    auto const direction  = startShouldBeOnTop_ ? 1.0f : -1.0f;
    auto const start      = startShouldBeOnTop_ ? bounds_.getY() : bounds_.getBottom();
    auto const proportion = bounds_.getHeight() * value;
    return static_cast<int>(start + (proportion * direction));
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