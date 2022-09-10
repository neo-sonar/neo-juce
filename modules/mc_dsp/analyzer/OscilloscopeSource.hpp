#ifndef MODERN_CIRCUITS_JUCE_MODULES_MC_DSP_OSCILLOSCOPE_SOURCE_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_MC_DSP_OSCILLOSCOPE_SOURCE_HPP

namespace mc {

struct OscilloscopeSource {
    OscilloscopeSource() = default;

    auto process(juce::AudioBuffer<float> const& buffer) -> void;
    auto process(juce::AudioBuffer<double> const& buffer) -> void;

    MC_NODISCARD auto currentScope() const noexcept -> Span<float const>;

    auto addChangeListener(juce::ChangeListener* l) -> void;
    auto removeChangeListener(juce::ChangeListener* l) -> void;

private:
    DownSamplingAnalyzer _source { 16U };
};

} // namespace mc

#endif // MODERN_CIRCUITS_JUCE_MODULES_MC_DSP_OSCILLOSCOPE_SOURCE_HPP
