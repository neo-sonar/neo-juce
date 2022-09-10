#ifndef MODERN_CIRCUITS_JUCE_MODULES_MULTI_MONO_IIR_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_MULTI_MONO_IIR_HPP

namespace mc {

template <typename SampleType>
struct MultiMonoIIR {
    // This processor only works with float & double as its sample type.
    static_assert(std::is_same<SampleType, float>::value || std::is_same<SampleType, double>::value, "[dsp]");

    MultiMonoIIR() = default;

    MC_NODISCARD auto getCoefficients() const noexcept -> juce::IIRCoefficients { return _coefficients; }

    auto setCoefficients(juce::IIRCoefficients const& newCoefficients) noexcept -> void
    {
        _coefficients = newCoefficients;
        updateFilters();
    }

    auto prepare(juce::dsp::ProcessSpec const& specs)
    {
        _specs = specs;
        createFilters();
        updateFilters();
    }

    auto reset() -> void
    {
        std::for_each(begin(_filters), end(_filters), [](auto& f) { f.reset(); });
    }

    template <typename ProcessContext>
    void process(const ProcessContext& context) noexcept
    {
        auto const& inputBlock = context.getInputBlock();
        auto& outputBlock      = context.getOutputBlock();

        jassert(inputBlock.getNumChannels() == outputBlock.getNumChannels());
        jassert(inputBlock.getNumSamples() == outputBlock.getNumSamples());

        outputBlock.copyFrom(inputBlock);

        auto const numSamples = outputBlock.getNumSamples();
        for (std::size_t i = 0; i < inputBlock.getNumChannels(); ++i) {
            auto* const channel = outputBlock.getChannelPointer(i);
            for (std::size_t j = 0; j < numSamples; ++j) {
                auto const input  = static_cast<float>(channel[j]);
                auto const output = _filters[i].processSingleSampleRaw(input);
                channel[j]        = static_cast<SampleType>(output);
            }
        }
    }

private:
    auto createFilters() -> void
    {
        _filters.clear();
        std::generate_n(std::back_inserter(_filters), _specs.numChannels, [] { return juce::IIRFilter {}; });
    }

    auto updateFilters() -> void
    {
        std::for_each(begin(_filters), end(_filters), [this](auto& f) { f.setCoefficients(_coefficients); });
    }

    juce::dsp::ProcessSpec _specs {};
    juce::IIRCoefficients _coefficients {};
    Vector<juce::IIRFilter> _filters {};
};
} // namespace mc

#endif // MODERN_CIRCUITS_JUCE_MODULES_MULTI_MONO_IIR_HPP
