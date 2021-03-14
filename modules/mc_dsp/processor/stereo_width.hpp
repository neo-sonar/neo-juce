/**
 * @file stereo_width.hpp
 * @copyright Copyright 2019-2020 Modern Circuits. All rights reserved.
 */

#pragma once

namespace mc::dsp
{

/**
 * @brief Controls the width of a stereo signal
 */
class StereoWidth
{
public:
    /**
     * @brief Holds the parameters for this processor.
     */
    struct Parameters
    {
        float width = 1.0f;  // 0 to 2.0: 1 = Normal, 0 = Mono
    };

    StereoWidth() = default;

    /**
     * @brief Returns true if the process is enabled.
     */
    [[nodiscard]] auto isEnabled() const noexcept -> bool { return enabled; }

    /**
     * @brief Enables/disables the process.
     */
    void setEnabled(bool newValue) noexcept { enabled = newValue; }

    /**
     * @brief Returns the process's current parameters.
     */
    [[nodiscard]] auto getParameters() const noexcept -> Parameters { return parameters; }

    /**
     * @brief Applies a new set of parameters to the process.
     *
     * Note that this doesn't attempt to lock the process,
     * so if you call this in parallel with
     * the process method, you may get artifacts.
     */
    void setParameters(Parameters const& newParams) { parameters = newParams; }

    /**
     * @brief Initialises the process.
     */
    void prepare(juce::dsp::ProcessSpec const& /*unused*/) { }

    /**
     * @brief Resets the process's internal state.
     */
    void reset() noexcept { }

    /**
     * @brief Applies the process to a stereo buffer.
     */
    template<typename ProcessContext>
    void process(const ProcessContext& context) noexcept
    {
        auto const& inputBlock                     = context.getInputBlock();
        auto& outputBlock                          = context.getOutputBlock();
        [[maybe_unused]] auto const numInChannels  = inputBlock.getNumChannels();
        [[maybe_unused]] auto const numOutChannels = outputBlock.getNumChannels();
        auto const numSamples                      = outputBlock.getNumSamples();

        // Check channel configuration
        jassert(inputBlock.getNumSamples() == numSamples);
        jassert(numInChannels == 2 && numOutChannels == 2);

        outputBlock.copyFrom(inputBlock);

        auto* const left  = outputBlock.getChannelPointer(0);
        auto* const right = outputBlock.getChannelPointer(1);

        auto const coef = parameters.width * 0.5f;

        for (size_t sample = 0; sample < numSamples; ++sample)
        {
            auto const inLeft  = left[sample];
            auto const inRight = right[sample];

            auto const mid  = (inLeft + inRight) * 0.5f;
            auto const side = (inRight - inLeft) * coef;

            auto const outLeft  = mid - side;
            auto const outRight = mid + side;

            left[sample]  = outLeft;
            right[sample] = outRight;
        }
    }

private:
    bool enabled          = true;
    Parameters parameters = {1.0f};
};

}  // namespace mc::dsp
