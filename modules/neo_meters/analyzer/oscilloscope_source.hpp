#pragma once

namespace neo {

struct OscilloscopeSource {
    OscilloscopeSource() = default;

    auto prepare(juce::dsp::ProcessSpec const& spec) -> void;
    auto process(juce::AudioBuffer<float> const& buffer) -> void;
    auto reset() -> void;

    [[nodiscard]] auto currentScope() const noexcept -> std::span<float const>;

    auto addChangeListener(juce::ChangeListener* l) -> void;
    auto removeChangeListener(juce::ChangeListener* l) -> void;

private:
    DownSamplingAnalyzer _source { 32U };
};

} // namespace neo
