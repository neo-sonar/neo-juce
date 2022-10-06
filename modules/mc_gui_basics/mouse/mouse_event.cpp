namespace mc {

auto hitTest(juce::MouseEvent const& event, juce::Rectangle<float> bounds) -> bool
{
    return bounds.contains(event.position);
}

auto hitTest(juce::MouseEvent const& event, juce::Point<float> point, float radius) -> bool
{
    return event.position.getDistanceFrom(point) <= radius;
}

} // namespace mc
