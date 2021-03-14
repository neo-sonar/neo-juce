namespace mc
{
XYPad::XYPad() : position_ {0.0f, 0.0f} { }

auto XYPad::paint(juce::Graphics& g) -> void
{
    g.fillAll(juce::Colours::pink);

    auto bounds = getLocalBounds();

    g.setColour(juce::Colours::black.withAlpha(0.8f));

    static constexpr auto numLines = 12;

    for (int i = 0; i < numLines; i++)
    {
        auto const lineX        = bounds.getX() + (bounds.getWidth() / numLines * i);
        auto const lineVertical = juce::Line<int> {lineX, bounds.getY(), lineX, bounds.getBottom()};
        g.drawLine(lineVertical.toFloat(), 1.0f);

        auto const lineY          = bounds.getY() + (bounds.getHeight() / numLines * i);
        auto const lineHorizontal = juce::Line<int> {bounds.getX(), lineY, bounds.getRight(), lineY};
        g.drawLine(lineHorizontal.toFloat(), 1.0f);
    }

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

auto XYPad::setXPosition(float x) noexcept -> void { position_.x = xRange_.convertTo0to1(x); }

auto XYPad::setYPosition(float y) noexcept -> void { position_.y = yRange_.convertTo0to1(y); }

auto XYPad::setNormalisedXPosition(float x) noexcept -> void { position_.x = x; }

auto XYPad::setNormalisedYPosition(float y) noexcept -> void { position_.y = y; }

auto XYPad::getXRange() const noexcept -> juce::NormalisableRange<float> { return xRange_; }

auto XYPad::getYRange() const noexcept -> juce::NormalisableRange<float> { return yRange_; }

auto XYPad::setXRange(juce::NormalisableRange<float> const& newRange) noexcept -> void { xRange_ = newRange; }

auto XYPad::setYRange(juce::NormalisableRange<float> const& newRange) noexcept -> void { yRange_ = newRange; }

auto XYPad::mouseMove(juce::MouseEvent const& event) -> void
{
    thumbColor_ = thumbHitTest(event) ? juce::Colours::yellow : juce::Colours::green;
    repaint();
}

auto XYPad::mouseDown(juce::MouseEvent const& event) -> void
{
    position_.x = getValueFromPixel(event.x, true);
    position_.y = getValueFromPixel(event.y, false);
    repaint();
}

auto XYPad::mouseDrag(juce::MouseEvent const& event) -> void
{
    position_.x = getValueFromPixel(event.x, true);
    position_.y = getValueFromPixel(event.y, false);

    if (event.x >= bounds_.getRight()) { position_.x = getValueFromPixel(bounds_.getRight(), true); }
    if (event.x <= bounds_.getX()) { position_.x = getValueFromPixel(bounds_.getX(), true); }
    if (event.y >= bounds_.getBottom()) { position_.y = getValueFromPixel(bounds_.getBottom(), false); }
    if (event.y <= bounds_.getY()) { position_.y = getValueFromPixel(bounds_.getY(), false); }
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