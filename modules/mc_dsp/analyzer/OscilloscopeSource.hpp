#pragma once

namespace mc {

struct OscilloscopeSource {
    OscilloscopeSource() = default;

    auto process(juce::AudioBuffer<float> const& buffer) -> void;
    auto process(juce::AudioBuffer<double> const& buffer) -> void;

    [[nodiscard]] auto currentScope() const noexcept -> Span<float const>;

    auto addChangeListener(juce::ChangeListener* l) -> void;
    auto removeChangeListener(juce::ChangeListener* l) -> void;

private:
    DownSamplingAnalyzer _source { 16U };
};

} // namespace mc
