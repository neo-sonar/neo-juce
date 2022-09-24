#pragma once

namespace mc {

struct Placeholder final : juce::Component {
    explicit Placeholder(juce::Colour color, juce::String text = {});
    ~Placeholder() override = default;

    auto paint(juce::Graphics& g) -> void override;

private:
    juce::Colour _color { juce::Colours::white };
    juce::String _text {};
};

} // namespace mc
