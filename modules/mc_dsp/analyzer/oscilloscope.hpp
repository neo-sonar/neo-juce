#ifndef MODERN_CIRCUITS_JUCE_MODULES_MC_DSP_OSCILLOSCOPE_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_MC_DSP_OSCILLOSCOPE_HPP

namespace mc
{

class Oscilloscope
    : public juce::Component
    , private juce::Timer
{
public:
    class LookAndFeelMethods
    {
    public:
        virtual ~LookAndFeelMethods() = default;

        virtual auto drawOscilloscopeBackground(juce::Graphics& g, juce::Rectangle<int> bounds) -> void = 0;
        virtual auto drawOscilloscopePlot(juce::Graphics& g, juce::Rectangle<int> bounds, double const* data,
                                          std::size_t numSamples, float scaler = 1.0f, float offset = 0.0f) -> void
            = 0;
    };

    explicit Oscilloscope(OscilloscopeSource& source);

    auto setFramesPerSecond(int framesPerSecond) -> void;

    auto paint(juce::Graphics& g) -> void override;

private:
    void timerCallback() override;

    OscilloscopeSource& oscilloscopeSource_;
    std::array<double, AudioBufferQueue<double>::bufferSize> sampleData {};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Oscilloscope)  // NOLINT
};

}  // namespace mc

#endif  // MODERN_CIRCUITS_JUCE_MODULES_MC_DSP_OSCILLOSCOPE_HPP
