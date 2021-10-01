#ifndef MODERN_CIRCUITS_JUCE_MODULES_MULTI_MONO_IIR_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_MULTI_MONO_IIR_HPP

namespace mc {

template <typename SampleType>
class MultiMonoIIR {
    // This processor only works with float & double as its sample type.
    static_assert(std::is_same<SampleType, float>::value || std::is_same<SampleType, double>::value, "");

public:
    MultiMonoIIR() = default;

    MC_NODISCARD auto getCoefficients() const noexcept -> juce::IIRCoefficients { return coefficients_; }

    auto setCoefficients(juce::IIRCoefficients const& newCoefficients) noexcept -> void
    {
        coefficients_ = newCoefficients;
        updateFilters();
    }

    auto prepare(juce::dsp::ProcessSpec const& specs)
    {
        specs_ = specs;
        createFilters();
        updateFilters();
    }

    auto reset() -> void
    {
        std::for_each(begin(filters_), end(filters_), [](auto& f) { f.reset(); });
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
                auto const output = filters_[i].processSingleSampleRaw(input);
                channel[j]        = static_cast<SampleType>(output);
            }
        }
    }

private:
    auto createFilters() -> void
    {
        filters_.clear();
        std::generate_n(std::back_inserter(filters_), specs_.numChannels, [] { return juce::IIRFilter {}; });
    }

    auto updateFilters() -> void
    {
        std::for_each(begin(filters_), end(filters_), [this](auto& f) { f.setCoefficients(coefficients_); });
    }

    juce::dsp::ProcessSpec specs_ {};
    juce::IIRCoefficients coefficients_ {};
    std::vector<juce::IIRFilter> filters_ {};
};
} // namespace mc

#endif // MODERN_CIRCUITS_JUCE_MODULES_MULTI_MONO_IIR_HPP
