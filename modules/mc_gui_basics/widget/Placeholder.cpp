
namespace mc {

Placeholder::Placeholder(juce::Colour color, juce::String text) : _color { color }, _text { std::move(text) } { }

auto Placeholder::paint(juce::Graphics& g) -> void
{
    g.fillAll(_color);
    g.setColour(juce::Colours::white);
    g.drawText(_text, getLocalBounds().toFloat(), juce::Justification::centred);
}

} // namespace mc
