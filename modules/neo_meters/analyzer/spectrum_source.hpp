#pragma once

namespace neo {

/// \brief Recieves data from the processor thread, calculates the FFT which is
/// read by the GUI thread to plot a spectrum.
struct SpectrumSource : juce::ChangeBroadcaster, juce::TimeSliceClient {
    explicit SpectrumSource(juce::TimeSliceThread& worker, int fftOrder = 10);
    ~SpectrumSource() override;

    SpectrumSource(SpectrumSource const& other)                    = delete;
    auto operator=(SpectrumSource const& other) -> SpectrumSource& = delete;

    SpectrumSource(SpectrumSource&& other)                    = delete;
    auto operator=(SpectrumSource&& other) -> SpectrumSource& = delete;

    [[nodiscard]] auto getSampleRate() const noexcept -> double;
    [[nodiscard]] auto getCurrentAverage() -> std::vector<float>;
    [[nodiscard]] auto makePath(juce::Rectangle<float> bounds) -> juce::Path;

    auto prepare(juce::dsp::ProcessSpec const& spec) -> void;

    template <typename ProcessContext>
    auto process(ProcessContext const& context) -> void;

    auto reset() -> void;

private:
    auto useTimeSlice() -> int override;

    auto processInternal(juce::dsp::AudioBlock<float> const& block) -> void;
    auto runTransform() -> void;
    auto dequeueBuffers() -> void;

    static constexpr auto maxSubBlockSize = std::size_t { 512 };

    juce::TimeSliceThread& _worker;
    juce::dsp::ProcessSpec _spec {};

    juce::dsp::FFT _fft;
    juce::dsp::WindowingFunction<float> _windowing;
    std::vector<float> _monoBuffer;
    std::vector<float> _fftBuffer {};

    Averager<float> _averager;
    std::mutex mutable _renderMutex {};

    LockFreeQueue<StaticVector<float, maxSubBlockSize>> _queue;
    int _numSamplesDequeued { 0 };

    std::atomic<bool> _shouldExit { false };
};

template <typename ProcessContext>
auto SpectrumSource::process(ProcessContext const& context) -> void
{
    auto inBlock  = context.getInputBlock();
    auto outBlock = context.getOutputBlock();
    if (ProcessContext::usesSeparateInputAndOutputBlocks()) { outBlock.copyFrom(inBlock); }
    processInternal(outBlock);
}

} // namespace neo
