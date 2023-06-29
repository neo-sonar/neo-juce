#pragma once

namespace mc {

struct DownSamplingAnalyzer final : juce::Timer, juce::ChangeBroadcaster {
    explicit DownSamplingAnalyzer(std::size_t downSampleFactor);
    ~DownSamplingAnalyzer() override = default;

    auto prepare(juce::dsp::ProcessSpec const& spec) -> void;
    auto process(juce::AudioBuffer<float> const& buffer) -> void;
    auto reset() -> void;

    [[nodiscard]] auto buffer() const noexcept -> std::span<float const>;

private:
    inline static constexpr auto chunkSize = 128U;

    auto timerCallback() -> void override;

    juce::dsp::StateVariableTPTFilter<float> _filter;
    juce::AudioBuffer<float> _filterBuffer;

    LockFreeQueue<StaticVector<float, chunkSize>> _queue { 8U };
    std::size_t _downSampleFactor { 8U };

    std::vector<float> _buffer;
};

} // namespace mc
