#pragma once

namespace mc {

struct DownSamplingAnalyzer final : juce::Timer, juce::ChangeBroadcaster {
    DownSamplingAnalyzer(std::size_t downSampleFactor);
    ~DownSamplingAnalyzer() override = default;

    void process(juce::AudioBuffer<float> const& buffer);
    void process(juce::AudioBuffer<double> const& buffer);

    MC_NODISCARD auto buffer() const noexcept -> span<float const>;

private:
    auto timerCallback() -> void override;

    enum { ChunkSize = 64U };
    LockFreeQueue<StaticVector<float, ChunkSize>> queue_ { 8U };
    std::size_t downSampleFactor_ { 8U };

    std::vector<float> buffer_;
};

} // namespace mc