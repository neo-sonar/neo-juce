#pragma once

namespace mc {

struct DownSamplingAnalyzer final : juce::Timer, juce::ChangeBroadcaster {
    explicit DownSamplingAnalyzer(std::size_t downSampleFactor);
    ~DownSamplingAnalyzer() override = default;

    void process(juce::AudioBuffer<float> const& buffer);
    void process(juce::AudioBuffer<double> const& buffer);

    [[nodiscard]] auto buffer() const noexcept -> Span<float const>;

private:
    auto timerCallback() -> void override;

    enum { ChunkSize = 64U };
    LockFreeQueue<StaticVector<float, ChunkSize>> _queue { 8U };
    std::size_t _downSampleFactor { 8U };

    Vector<float> _buffer;
};

} // namespace mc
