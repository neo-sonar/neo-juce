void setupDefaultStereoFieldColours() override
{
    setColour(StereoFieldComponent::backgroundColour, juce::Colour(0xff050a29));
    setColour(StereoFieldComponent::borderColour, juce::Colours::silver);
    setColour(StereoFieldComponent::outlineColour, juce::Colours::silver);
    setColour(StereoFieldComponent::gonioColour, juce::Colours::silver);
    setColour(StereoFieldComponent::currentValuesColour, juce::Colours::silver);
    setColour(StereoFieldComponent::maxValuesColour, juce::Colours::darkgrey);
}

void drawGonioBackground(juce::Graphics& g, juce::Rectangle<float> bounds, float margin, float border) override
{
    auto colour = findColour(StereoFieldComponent::backgroundColour);
    g.fillAll(colour);
    colour = findColour(StereoFieldComponent::borderColour);
    g.setColour(colour);
    g.drawRoundedRectangle(bounds.reduced(margin * 0.5f), margin * 0.5f, border);

    colour = findColour(StereoFieldComponent::outlineColour);
    g.setColour(colour);
    auto size      = std::min(bounds.getWidth(), bounds.getHeight());
    auto oscBounds = bounds.withSizeKeepingCentre(size, size).reduced(10);
    g.drawEllipse(oscBounds.toFloat(), 1.0);
}

void drawGonioMeter(juce::Graphics& g, juce::Rectangle<float> bounds, const StereoFieldBuffer<float>& stereoBuffer,
                    int leftIdx, int rightIdx) override
{
    auto colour = findColour(StereoFieldComponent::gonioColour);
    g.setColour(colour);

    auto size        = std::min(bounds.getWidth(), bounds.getHeight());
    auto oscBounds   = bounds.withSizeKeepingCentre(size, size);
    auto osciloscope = stereoBuffer.getOscilloscope(512, oscBounds.toFloat(), leftIdx, rightIdx);
    g.strokePath(osciloscope, juce::PathStrokeType(1.0));
}

void drawStereoFieldBackground(juce::Graphics& g, juce::Rectangle<float> bounds, float margin, float border) override
{
    g.drawRoundedRectangle(bounds.reduced(margin * 0.5f), margin * 0.5f, border);
    auto graph = bounds.reduced(margin);
    juce::Path background;
    background.addRectangle(graph);
    background.addCentredArc(graph.getCentreX(), graph.getBottom(), 0.5f * graph.getWidth(), 0.5f * graph.getWidth(),
                             0.0f, 1.5f * juce::MathConstants<float>::pi, 2.5f * juce::MathConstants<float>::pi);
    background.addCentredArc(graph.getCentreX(), graph.getBottom(), 0.25f * graph.getWidth(), 0.25f * graph.getWidth(),
                             0.0f, 1.5f * juce::MathConstants<float>::pi, 2.5f * juce::MathConstants<float>::pi);
    const auto d = graph.getWidth() * 0.5f / std::sqrt(2.0f);
    background.addLineSegment(
        juce::Line<float>(graph.getCentreX(), graph.getBottom(), graph.getCentreX() - d, graph.getBottom() - d), 1.0f);
    background.addLineSegment(juce::Line<float>(graph.getCentreX(), graph.getBottom(), graph.getCentreX(),
                                                graph.getBottom() - graph.getWidth() * 0.5f),
                              1.0f);
    background.addLineSegment(
        juce::Line<float>(graph.getCentreX(), graph.getBottom(), graph.getCentreX() + d, graph.getBottom() - d), 1.0f);
    g.strokePath(background, juce::PathStrokeType(1.0));
}

void drawStereoField([[maybe_unused]] juce::Graphics& g, [[maybe_unused]] juce::Rectangle<float> bounds,
                     [[maybe_unused]] const StereoFieldBuffer<float>& /*unused*/, [[maybe_unused]] int leftIdx = 0,
                     [[maybe_unused]] int rightIdx = 1) override
{
    juce::ignoreUnused(g);
    juce::ignoreUnused(bounds);
    juce::ignoreUnused(leftIdx, rightIdx);
}
