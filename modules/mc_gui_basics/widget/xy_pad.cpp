namespace mc
{
XYPad::XYPad() : position_ {0.0f, 0.0f} { }

auto XYPad::paint(juce::Graphics& g) -> void
{
    auto const numLines = 6;
    auto const bounds   = bounds_.toFloat();

    // grid
    auto const colour = juce::Colours::darkgrey;
    auto const light  = colour.withAlpha(0.01f);
    g.setColour(colour);

    auto const intervalWidth  = bounds.getWidth() / numLines;
    auto const halfWidth      = bounds.getWidth() / 2.0f;
    auto const intervalHeight = bounds.getHeight() / numLines;
    auto const halfHeight     = bounds.getHeight() / 2.0f;

    auto const topGradient    = juce::ColourGradient::vertical(light, bounds.getY(), colour, halfHeight);
    auto const bottomGradient = juce::ColourGradient::vertical(colour, halfHeight, light, bounds.getBottom());

    auto const leftGradient  = juce::ColourGradient::horizontal(light, bounds.getX(), colour, halfWidth);
    auto const rightGradient = juce::ColourGradient::horizontal(colour, halfWidth, light, bounds.getRight());

    for (int i = 1; i < numLines; i++)
    {
        auto const idx          = static_cast<float>(i);
        auto const widthOffset  = intervalWidth * idx;
        auto const heightOffset = intervalHeight * idx;

        g.setGradientFill(topGradient);
        g.drawVerticalLine(static_cast<int>(bounds.getX() + widthOffset), bounds.getY(), halfHeight);

        g.setGradientFill(bottomGradient);
        g.drawVerticalLine(static_cast<int>(bounds.getX() + widthOffset), halfHeight, bounds.getBottom());

        g.setGradientFill(leftGradient);
        g.drawHorizontalLine(static_cast<int>(bounds.getY() + heightOffset), bounds.toFloat().getX(), halfWidth);

        g.setGradientFill(rightGradient);
        g.drawHorizontalLine(static_cast<int>(bounds.getY() + heightOffset), halfWidth, bounds.toFloat().getRight());
    }

    // thumb
    g.setColour(thumbColor_);
    auto const x = getPixelFromValue(position_.x, true);
    auto const y = getPixelFromValue(position_.y, false);
    thumb_       = thumb_.withCentre({static_cast<int>(x), static_cast<int>(y)});
    g.fillEllipse(thumb_.toFloat());
}

auto XYPad::resized() -> void { bounds_ = getLocalBounds(); }

auto XYPad::getXPosition() const noexcept -> float { return xRange_.convertFrom0to1(position_.x); }

auto XYPad::getYPosition() const noexcept -> float { return yRange_.convertFrom0to1(position_.y); }

auto XYPad::getNormalisedXPosition() const noexcept -> float { return position_.x; }

auto XYPad::getNormalisedYPosition() const noexcept -> float { return position_.y; }

auto XYPad::setXPosition(float x) noexcept -> void { setNormalisedXPosition(xRange_.convertTo0to1(x)); }

auto XYPad::setYPosition(float y) noexcept -> void { setNormalisedYPosition(yRange_.convertTo0to1(y)); }

auto XYPad::setNormalisedXPosition(float x) noexcept -> void
{
    position_.x = x;
    listeners_.call([this](Listener& listener) { listener.xypadChanged(this, {getXPosition(), getYPosition()}); });
}

auto XYPad::setNormalisedYPosition(float y) noexcept -> void
{
    position_.y = y;
    listeners_.call([this](Listener& listener) { listener.xypadChanged(this, {getXPosition(), getYPosition()}); });
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
    setYPosition(getValueFromPixel(event.y, true));
    listeners_.call([this](Listener& listener) { listener.xypadDragStarted(this); });
    thumbColor_ = juce::Colours::white;
    repaint();
}

auto XYPad::mouseUp(juce::MouseEvent const& event) -> void
{
    juce::ignoreUnused(event);
    listeners_.call([this](Listener& listener) { listener.xypadDragEnded(this); });
    repaint();
}

auto XYPad::mouseDrag(juce::MouseEvent const& event) -> void
{
    setXPosition(getValueFromPixel(event.x, true));
    setYPosition(getValueFromPixel(event.y, true));

    if (event.x >= bounds_.getRight()) { setXPosition(getValueFromPixel(bounds_.getRight(), true)); }
    if (event.x <= bounds_.getX()) { setXPosition(getValueFromPixel(bounds_.getX(), true)); }
    if (event.y >= bounds_.getBottom()) { setYPosition(getValueFromPixel(bounds_.getBottom(), false)); }
    if (event.y <= bounds_.getY()) { setYPosition(getValueFromPixel(bounds_.getY(), false)); }
    repaint();
}

auto XYPad::getValueFromPixel(int pixel, bool isXAxis) const -> float
{
    auto const x      = static_cast<float>(bounds_.getX());
    auto const y      = static_cast<float>(bounds_.getY());
    auto const right  = static_cast<float>(bounds_.getRight());
    auto const bottom = static_cast<float>(bounds_.getBottom());

    if (isXAxis) { return juce::jmap<float>(static_cast<float>(pixel), x, right, 0.0f, 1.0f); }
    return juce::jmap<float>(static_cast<float>(pixel), y, bottom, 0.0f, 1.0f);
}

auto XYPad::getPixelFromValue(float value, bool x) const -> int
{
    if (x) { return static_cast<int>(bounds_.getX() + (value * bounds_.getWidth())); }
    return static_cast<int>(bounds_.getY() + value * bounds_.getHeight());
}

auto XYPad::thumbHitTest(juce::MouseEvent const& event) const -> bool
{
    auto const isInXPosition = event.x >= thumb_.getX() && event.x <= thumb_.getRight();
    auto const isInYPosition = event.y >= thumb_.getY() && event.y <= thumb_.getBottom();
    return isInXPosition && isInYPosition;
}

}  // namespace mc