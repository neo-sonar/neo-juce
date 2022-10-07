#pragma once

namespace mc::fx {

/// \brief Controls the width of a stereo signal
struct StereoWidth {
    /// \brief Holds the parameters for this processor.
    struct Parameters {
        float width = 1.0F; // 0 to 2.0: 1 = Normal, 0 = Mono
    };

    StereoWidth() = default;

    /// \brief Returns true if the process is enabled.
    [[nodiscard]] auto isEnabled() const noexcept -> bool { return _enabled; }

    /// \brief Enables/disables the process.
    void setEnabled(bool newValue) noexcept { _enabled = newValue; }

    /// \brief Returns the process's current parameters.
    [[nodiscard]] auto getParameters() const noexcept -> Parameters { return _parameters; }

    /// \brief Applies a new set of parameters to the process.
    ///
    /// Note that this doesn't attempt to lock the process,
    /// so if you call this in parallel with
    /// the process method, you may get artifacts.
    void setParameters(Parameters const& newParams) { _parameters = newParams; }

    /// \brief Initialises the process.
    void prepare(juce::dsp::ProcessSpec const& /*unused*/) { }

    /// \brief Resets the process's internal state.
    void reset() noexcept { }

    /// \brief Applies the process to a stereo buffer.
    template <typename ProcessContext>
    void process(ProcessContext const& context) noexcept
    {
        auto const& inputBlock    = context.getInputBlock();
        auto& outputBlock         = context.getOutputBlock();
        auto const numInChannels  = inputBlock.getNumChannels();
        auto const numOutChannels = outputBlock.getNumChannels();
        auto const numSamples     = outputBlock.getNumSamples();

        // Check channel configuration
        jassert(inputBlock.getNumSamples() == numSamples);
        jassert(numInChannels == 2 && numOutChannels == 2);
        (void)numInChannels;
        (void)numOutChannels;

        outputBlock.copyFrom(inputBlock);

        auto* const left  = outputBlock.getChannelPointer(0);
        auto* const right = outputBlock.getChannelPointer(1);

        auto const coef = _parameters.width * 0.5F;

        for (size_t sample = 0; sample < numSamples; ++sample) {
            auto const inLeft  = left[sample];
            auto const inRight = right[sample];

            auto const mid  = (inLeft + inRight) * 0.5F;
            auto const side = (inRight - inLeft) * coef;

            auto const outLeft  = mid - side;
            auto const outRight = mid + side;

            left[sample]  = outLeft;
            right[sample] = outRight;
        }
    }

private:
    bool _enabled          = true;
    Parameters _parameters = { 1.0F };
};

} // namespace mc::fx
