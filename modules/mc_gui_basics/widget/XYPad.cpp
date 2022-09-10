namespace mc {
XYPad::XYPad(juce::String const& name) : juce::Component { name }, _normalizedValues { 0.0F, 0.0F } { }

auto XYPad::paint(juce::Graphics& g) -> void
{
    auto* lnf = dynamic_cast<XYPad::LookAndFeelMethods*>(&getLookAndFeel());
    if (lnf != nullptr) {
        auto const x        = getPixelFromNormalizedValue(_normalizedValues.x, true);
        auto const y        = getPixelFromNormalizedValue(_normalizedValues.y, false);
        auto const diameter = lnf->getXYPadThumbDiameter(*this);
        _thumb              = juce::Rectangle<int> { 0, 0, diameter, diameter }.withCentre(
            { static_cast<int>(x), static_cast<int>(y) });
        lnf->drawXYPad(g, _thumb.toFloat(), *this);
        return;
    }

    jassertfalse;
}

auto XYPad::resized() -> void { _bounds = getLocalBounds(); }

auto XYPad::getValueX() const noexcept -> float { return _xRange.convertFrom0to1(_normalizedValues.x); }

auto XYPad::getValueY() const noexcept -> float { return _yRange.convertFrom0to1(_normalizedValues.y); }

auto XYPad::getNormalizedX() const noexcept -> float { return _normalizedValues.x; }

auto XYPad::getNormalizedY() const noexcept -> float { return _normalizedValues.y; }

auto XYPad::setValueX(float x) -> void { setNormalizedX(_xRange.convertTo0to1(x)); }

auto XYPad::setValueY(float y) -> void { setNormalizedY(_yRange.convertTo0to1(y)); }

auto XYPad::setNormalizedX(float x) -> void
{
    _normalizedValues.x = x;
    updatePosition();
}

auto XYPad::setNormalizedY(float y) -> void
{
    _normalizedValues.y = y;
    updatePosition();
}

auto XYPad::getXRange() const noexcept -> juce::NormalisableRange<float> { return _xRange; }

auto XYPad::getYRange() const noexcept -> juce::NormalisableRange<float> { return _yRange; }

auto XYPad::getDirectionX() const noexcept -> bool { return _startShouldBeOnLeft; }

auto XYPad::getDirectionY() const noexcept -> bool { return _startShouldBeOnTop; }

auto XYPad::setDirectionX(bool startShouldBeOnLeft) -> void { _startShouldBeOnLeft = startShouldBeOnLeft; }

auto XYPad::setDirectionY(bool startShouldBeOnTop) -> void { _startShouldBeOnTop = startShouldBeOnTop; }

auto XYPad::setXRange(juce::NormalisableRange<float> const& newRange) -> void { _xRange = newRange; }

auto XYPad::setYRange(juce::NormalisableRange<float> const& newRange) -> void { _yRange = newRange; }

auto XYPad::isOverThumb() const noexcept -> bool { return _isOverThumb; }
auto XYPad::isDragging() const noexcept -> bool { return _isDragging; }

auto XYPad::mouseMove(juce::MouseEvent const& event) -> void
{
    _isOverThumb = thumbHitTest(event);
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
    if (!_isDragging) { startDragging(); }

    auto p = juce::Point<int> {};
    p.x    = clamp<int>(event.x, _bounds.getX(), _bounds.getRight());
    p.y    = clamp<int>(event.y, _bounds.getY(), _bounds.getBottom());
    setValueX(getValueFromPixel(p.x, true));
    setValueY(getValueFromPixel(p.y, false));
}

auto XYPad::getValueFromPixel(int pixel, bool isXAxis) const -> float
{
    auto const x      = static_cast<float>(_bounds.getX());
    auto const y      = static_cast<float>(_bounds.getY());
    auto const right  = static_cast<float>(_bounds.getRight());
    auto const bottom = static_cast<float>(_bounds.getBottom());

    if (isXAxis) {
        auto const startX = _startShouldBeOnLeft ? _xRange.start : _xRange.end;
        auto const endX   = _startShouldBeOnLeft ? _xRange.end : _xRange.start;
        return juce::jmap<float>(static_cast<float>(pixel), x, right, startX, endX);
    }

    auto const startY = _startShouldBeOnTop ? _yRange.start : _yRange.end;
    auto const endY   = _startShouldBeOnTop ? _yRange.end : _yRange.start;
    return juce::jmap<float>(static_cast<float>(pixel), y, bottom, startY, endY);
}

auto XYPad::getPixelFromNormalizedValue(float value, bool x) const -> int
{
    if (x) {
        auto const direction  = _startShouldBeOnLeft ? 1.0F : -1.0F;
        auto const start      = _startShouldBeOnLeft ? _bounds.getX() : _bounds.getRight();
        auto const proportion = static_cast<float>(_bounds.getWidth()) * value;
        return static_cast<int>(static_cast<float>(start) + (proportion * direction));
    }

    auto const direction  = _startShouldBeOnTop ? 1.0F : -1.0F;
    auto const start      = _startShouldBeOnTop ? _bounds.getY() : _bounds.getBottom();
    auto const proportion = static_cast<float>(_bounds.getHeight()) * value;
    return static_cast<int>(static_cast<float>(start) + (proportion * direction));
}

auto XYPad::thumbHitTest(juce::MouseEvent const& event) const -> bool
{
    auto const isInXPosition = (event.x >= _thumb.getX()) && (event.x <= _thumb.getRight());
    auto const isInYPosition = (event.y >= _thumb.getY()) && (event.y <= _thumb.getBottom());
    return isInXPosition && isInYPosition;
}

auto XYPad::startDragging() -> void
{
    _isDragging = true;
    _listeners.call([this](Listener& listener) { listener.xypadDragStarted(this); });
    repaint();
}

auto XYPad::stopDragging() -> void
{
    _isDragging = false;
    _listeners.call([this](Listener& listener) { listener.xypadDragEnded(this); });
    repaint();
}

auto XYPad::updatePosition() -> void
{
    _listeners.call([this](Listener& listener) { listener.xypadChanged(this, { getValueX(), getValueY() }); });
    repaint();
}
} // namespace mc
