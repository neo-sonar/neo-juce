#pragma once

namespace neo {

struct OscilloscopeLookAndFeelMethods {
    OscilloscopeLookAndFeelMethods()          = default;
    virtual ~OscilloscopeLookAndFeelMethods() = default;

    virtual auto drawOscilloscopeBackground(juce::Graphics& g, juce::Rectangle<int> bounds) -> void = 0;
    virtual auto drawOscilloscopePlot(juce::Graphics& g,
        juce::Rectangle<int> area,
        OscilloscopeSource const& source,
        float scaler,
        float offset) -> void
        = 0;
};
struct Oscilloscope final : juce::Component, juce::ChangeListener {

    using LookAndFeelMethods = OscilloscopeLookAndFeelMethods;

    explicit Oscilloscope(OscilloscopeSource& source);
    ~Oscilloscope() override;

    auto paint(juce::Graphics& g) -> void override;
    auto changeListenerCallback(juce::ChangeBroadcaster* source) -> void override;

private:
    OscilloscopeSource& _source;

    JUCE_LEAK_DETECTOR(Oscilloscope) // NOLINT
};

} // namespace neo
