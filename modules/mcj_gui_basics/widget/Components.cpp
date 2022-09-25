namespace mc {

auto drawRoundedBorder(juce::Graphics& g, juce::Rectangle<float> area, juce::Colour color) -> void
{
    g.setColour(color);
    g.drawRoundedRectangle(area, 10.0F, 2.0F);
}

auto drawRoundedBorder(juce::Graphics& g, juce::Rectangle<int> area, juce::Colour color) -> void
{
    drawRoundedBorder(g, area.toFloat(), color);
}

auto drawRoundedBorder(juce::Graphics& g, juce::Component& component, juce::Colour color) -> void
{
    drawRoundedBorder(g, component.getBounds(), color);
}

} // namespace mc
