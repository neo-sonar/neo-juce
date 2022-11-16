
namespace mc {

Placeholder::Placeholder(juce::Colour color, juce::String text)
    : Placeholder { Spec { color, juce::Colours::white, std::move(text) } }
{
}

Placeholder::Placeholder(Spec spec) : _spec { std::move(spec) } { }

auto Placeholder::paint(juce::Graphics& g) -> void
{
    g.fillAll(_spec.backgroundColor);
    g.setColour(_spec.textColor);
    g.drawText(_spec.text, getLocalBounds().toFloat(), juce::Justification::centred);
}

} // namespace mc
