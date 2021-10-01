#ifndef MODERN_CIRCUITS_PLUGINS_SPECTRUM_ANALYZER_HPP
#define MODERN_CIRCUITS_PLUGINS_SPECTRUM_ANALYZER_HPP

namespace mc {
/**
 * @brief Recieves data from the processor thread, calculates the FFT which is
 * read by the GUI thread to plot a spectrum.
 */
class SpectrumSource : public juce::Thread {
public:
    SpectrumSource();
    ~SpectrumSource() override = default;

    SpectrumSource(const SpectrumSource& other) = delete;
    SpectrumSource(SpectrumSource&& other)      = delete;
    auto operator=(const SpectrumSource& rhs) -> SpectrumSource& = delete;
    auto operator=(SpectrumSource&& rhs) -> SpectrumSource& = delete;

    auto addAudioData(juce::AudioBuffer<float> const& buffer, int startChannel, int numChannels) -> void;
    auto setupAnalyser(int audioFifoSize, double sampleRateToUse) -> void;

    auto createPath(juce::Path& p, juce::Rectangle<float> const& bounds, float minFreq) -> void;
    MC_NODISCARD auto checkForNewData() -> bool;

private:
    auto run() -> void override;

    MC_NODISCARD auto indexToX(float index, float minFreq) const -> float;
    MC_NODISCARD static auto binToY(float bin, juce::Rectangle<float> const& bounds) -> float;

    float sampleRate_ {};

    juce::AbstractFifo abstractFifo_ { 48000 };
    juce::AudioBuffer<float> audioFifo_;
    juce::AudioBuffer<float> fftBuffer_;
    juce::AudioBuffer<float> averager_;

    int averagerPtr_ = 1;
    std::atomic<bool> newDataAvailable_ { false };

    juce::WaitableEvent waitForData_;
    juce::CriticalSection pathCreationLock_;

    juce::dsp::FFT fft_;
    juce::dsp::WindowingFunction<float> windowing_;

    JUCE_LEAK_DETECTOR(SpectrumSource) // NOLINT
};
} // namespace mc
#endif // MODERN_CIRCUITS_PLUGINS_SPECTRUM_ANALYZER_HPP
