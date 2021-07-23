namespace mc {
XYPad::XYPad(juce::String name)
    : juce::Component { name }, normalizedValues_ { 0.0f, 0.0f } { }

auto XYPad::paint(juce::Graphics& g) -> void
{
    if (auto* lnf = dynamic_cast<XYPad::LookAndFeelMethods*>(&getLookAndFeel()); lnf != nullptr) {
        auto const x        = getPixelFromNormalizedValue(normalizedValues_.x, true);
        auto const y        = getPixelFromNormalizedValue(normalizedValues_.y, false);
        auto const diameter = lnf->getXYPadThumbDiameter(*this);
        thumb_              = juce::Rectangle { 0, 0, diameter, diameter }.withCentre({ static_cast<int>(x), static_cast<int>(y) });
        lnf->drawXYPad(g, thumb_.toFloat(), *this);
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
    updatePosition();
}

auto XYPad::setNormalizedY(float y) -> void
{
    normalizedValues_.y = y;
    updatePosition();
}

auto XYPad::getXRange() const noexcept -> juce::NormalisableRange<float> { return xRange_; }

auto XYPad::getYRange() const noexcept -> juce::NormalisableRange<float> { return yRange_; }

auto XYPad::getDirectionX() const noexcept -> bool { return startShouldBeOnLeft_; }

auto XYPad::getDirectionY() const noexcept -> bool { return startShouldBeOnTop_; }

auto XYPad::setDirectionX(bool startShouldBeOnLeft) -> void { startShouldBeOnLeft_ = startShouldBeOnLeft; }

auto XYPad::setDirectionY(bool startShouldBeOnTop) -> void { startShouldBeOnTop_ = startShouldBeOnTop; }

auto XYPad::setXRange(juce::NormalisableRange<float> const& newRange) -> void { xRange_ = newRange; }

auto XYPad::setYRange(juce::NormalisableRange<float> const& newRange) -> void { yRange_ = newRange; }

auto XYPad::isOverThumb() const noexcept -> bool { return isOverThumb_; }
auto XYPad::isDragging() const noexcept -> bool { return isDragging_; }

auto XYPad::mouseMove(juce::MouseEvent const& event) -> void
{
    isOverThumb_ = thumbHitTest(event);
    repaint();
}

auto XYPad::mouseDown(juce::MouseEvent const& event) -> void
{
    setValueX(getValueFromPixel(event.x, true));
    setValueY(getValueFromPixel(event.y, false));
}

auto XYPad::mouseUp(juce::MouseEvent const& event) -> void
{
    juce::ignoreUnused(event);
    stopDragging();
}

auto XYPad::mouseDrag(juce::MouseEvent const& event) -> void
{
    if (!isDragging_) {
        startDragging();
    }

    auto p = juce::Point<int> {};
    p.x    = std::clamp<int>(event.x, bounds_.getX(), bounds_.getRight());
    p.y    = std::clamp<int>(event.y, bounds_.getY(), bounds_.getBottom());
    setValueX(getValueFromPixel(p.x, true));
    setValueY(getValueFromPixel(p.y, false));
}

auto XYPad::getValueFromPixel(int pixel, bool isXAxis) const -> float
{
    auto const x      = static_cast<float>(bounds_.getX());
    auto const y      = static_cast<float>(bounds_.getY());
    auto const right  = static_cast<float>(bounds_.getRight());
    auto const bottom = static_cast<float>(bounds_.getBottom());

    if (isXAxis) {
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
    if (x) {
        auto const direction  = startShouldBeOnLeft_ ? 1.0f : -1.0f;
        auto const start      = startShouldBeOnLeft_ ? bounds_.getX() : bounds_.getRight();
        auto const proportion = static_cast<float>(bounds_.getWidth()) * value;
        return static_cast<int>(static_cast<float>(start) + (proportion * direction));
    }

    auto const direction  = startShouldBeOnTop_ ? 1.0f : -1.0f;
    auto const start      = startShouldBeOnTop_ ? bounds_.getY() : bounds_.getBottom();
    auto const proportion = static_cast<float>(bounds_.getHeight()) * value;
    return static_cast<int>(static_cast<float>(start) + (proportion * direction));
}

auto XYPad::thumbHitTest(juce::MouseEvent const& event) const -> bool
{
    auto const isInXPosition = (event.x >= thumb_.getX()) && (event.x <= thumb_.getRight());
    auto const isInYPosition = (event.y >= thumb_.getY()) && (event.y <= thumb_.getBottom());
    return isInXPosition && isInYPosition;
}

auto XYPad::startDragging() -> void
{
    isDragging_ = true;
    listeners_.call([this](Listener& listener) { listener.xypadDragStarted(this); });
    repaint();
}

auto XYPad::stopDragging() -> void
{
    isDragging_ = false;
    listeners_.call([this](Listener& listener) { listener.xypadDragEnded(this); });
    repaint();
}

auto XYPad::updatePosition() -> void
{
    listeners_.call([this](Listener& listener) { listener.xypadChanged(this, { getValueX(), getValueY() }); });
    repaint();
}
} // namespace mc