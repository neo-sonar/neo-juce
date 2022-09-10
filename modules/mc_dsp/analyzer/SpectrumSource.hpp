#pragma once

namespace mc {

/// \brief Recieves data from the processor thread, calculates the FFT which is
/// read by the GUI thread to plot a spectrum.
struct SpectrumSource final : juce::Thread {
    SpectrumSource();
    ~SpectrumSource() override = default;

    SpectrumSource(const SpectrumSource& other)                  = delete;
    SpectrumSource(SpectrumSource&& other)                       = delete;
    auto operator=(const SpectrumSource& rhs) -> SpectrumSource& = delete;
    auto operator=(SpectrumSource&& rhs) -> SpectrumSource&      = delete;

    auto addAudioData(juce::AudioBuffer<float> const& buffer, int startChannel, int numChannels) -> void;
    auto setupAnalyser(int audioFifoSize, double sampleRateToUse) -> void;

    auto createPath(juce::Path& p, juce::Rectangle<float> const& bounds, float minFreq) -> void;
    MC_NODISCARD auto checkForNewData() -> bool;

private:
    auto run() -> void override;

    MC_NODISCARD auto indexToX(float index, float minFreq) const -> float;
    MC_NODISCARD static auto binToY(float bin, juce::Rectangle<float> const& bounds) -> float;

    float _sampleRate {};

    juce::AbstractFifo _abstractFifo { 48000 };
    juce::AudioBuffer<float> _audioFifo;
    juce::AudioBuffer<float> _fftBuffer;
    juce::AudioBuffer<float> _averager;

    int _averagerPtr = 1;
    Atomic<bool> _newDataAvailable { false };

    juce::WaitableEvent _waitForData;
    juce::CriticalSection _pathCreationLock;

    juce::dsp::FFT _fft;
    juce::dsp::WindowingFunction<float> _windowing;

    JUCE_LEAK_DETECTOR(SpectrumSource) // NOLINT
};
} // namespace mc
