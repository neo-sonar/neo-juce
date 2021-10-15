#ifndef MODERN_CIRCUITS_JUCE_MODULES_MC_DSP_OSCILLOSCOPE_SOURCE_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_MC_DSP_OSCILLOSCOPE_SOURCE_HPP

namespace mc {

struct OscilloscopeSource final : juce::Timer, juce::ChangeBroadcaster {
    OscilloscopeSource();
    ~OscilloscopeSource() override = default;

    OscilloscopeSource(OscilloscopeSource const& other) = delete;
    OscilloscopeSource(OscilloscopeSource&& other)      = delete;

    auto operator=(OscilloscopeSource const& other) -> OscilloscopeSource& = delete;
    auto operator=(OscilloscopeSource&& other) -> OscilloscopeSource& = delete;

    void process(juce::AudioBuffer<float> const& buffer);
    void process(juce::AudioBuffer<double> const& buffer);

    MC_NODISCARD auto currentScope() const noexcept -> span<float const>;

private:
    auto timerCallback() -> void override;

    enum { ChunkSize = 64U };
    LockFreeQueue<StaticVector<float, ChunkSize>> queue_ { 8U };
    std::size_t downSampleFactor_ { 8U };

    std::vector<float> currentScope_;

    JUCE_LEAK_DETECTOR(OscilloscopeSource) // NOLINT
};

} // namespace mc

#endif // MODERN_CIRCUITS_JUCE_MODULES_MC_DSP_OSCILLOSCOPE_SOURCE_HPP
