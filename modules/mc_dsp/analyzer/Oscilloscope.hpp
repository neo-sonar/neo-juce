#ifndef MODERN_CIRCUITS_JUCE_MODULES_MC_DSP_OSCILLOSCOPE_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_MC_DSP_OSCILLOSCOPE_HPP

namespace mc {

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
    OscilloscopeSource& source_;

    JUCE_LEAK_DETECTOR(Oscilloscope) // NOLINT
};

} // namespace mc

#endif // MODERN_CIRCUITS_JUCE_MODULES_MC_DSP_OSCILLOSCOPE_HPP
