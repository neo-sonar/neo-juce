#ifndef MODERN_CIRCUITS_PLUGINS_SPECTRUM_ANALYZER_HPP
#define MODERN_CIRCUITS_PLUGINS_SPECTRUM_ANALYZER_HPP

namespace mc
{
/**
 * @brief Recieves data from the processor thread, calculates the FFT which is
 * read by the GUI thread to plot a spectrum.
 */
class SpectrumSource : public juce::Thread
{
public:
    SpectrumSource();
    ~SpectrumSource() override = default;

    auto addAudioData(juce::AudioBuffer<float> const& buffer, int startChannel, int numChannels) -> void;
    auto setupAnalyser(int audioFifoSize, double sampleRateToUse) -> void;

    auto createPath(juce::Path& p, juce::Rectangle<float> const& bounds, float minFreq) -> void;
    [[nodiscard]] auto checkForNewData() -> bool;

private:
    auto run() -> void override;

    [[nodiscard]] auto indexToX(float index, float minFreq) const -> float;
    [[nodiscard]] static auto binToY(float bin, juce::Rectangle<float> const& bounds) -> float;

    float sampleRate {};

    juce::AbstractFifo abstractFifo_ {48000};
    juce::AudioBuffer<float> audioFifo_;
    juce::AudioBuffer<float> fftBuffer_;
    juce::AudioBuffer<float> averager_;

    int averagerPtr                    = 1;
    std::atomic<bool> newDataAvailable = false;

    juce::WaitableEvent waitForData;
    juce::CriticalSection pathCreationLock;

    juce::dsp::FFT fft {12};
    juce::dsp::WindowingFunction<float> windowing {size_t(fft.getSize()), juce::dsp::WindowingFunction<float>::kaiser};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SpectrumSource)  // NOLINT
};
}  // namespace mc
#endif  // MODERN_CIRCUITS_PLUGINS_SPECTRUM_ANALYZER_HPP
