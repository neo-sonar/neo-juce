#ifndef MODERN_CIRCUITS_JUCE_MODULES_MC_DSP_OSCILLOSCOPE_SOURCE_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_MC_DSP_OSCILLOSCOPE_SOURCE_HPP

namespace mc
{

class OscilloscopeSource
{
public:
    OscilloscopeSource() = default;

    void process(juce::AudioBuffer<float> const& buffer);
    void process(juce::AudioBuffer<double> const& buffer);

    [[nodiscard]] auto getQueue() -> AudioBufferQueue<double>&;

private:
    template<typename SampleType>
    void processInternal(SampleType const* data, std::size_t numSamples)
    {
        std::size_t index = 0;

        if (state_ == State::waitingForTrigger)
        {
            while (index++ < numSamples)
            {
                auto currentSample = *data++;

                if (currentSample >= triggerLevel_ && prevSample_ < triggerLevel_)
                {
                    numCollected_ = 0;
                    state_        = State::collecting;
                    break;
                }

                prevSample_ = currentSample;
            }
        }

        if (state_ == State::collecting)
        {
            while (index++ < numSamples)
            {
                buffer_.at(numCollected_++) = *data++;

                if (numCollected_ == buffer_.size())
                {
                    audioBufferQueue_.push(buffer_.data(), buffer_.size());
                    state_      = State::waitingForTrigger;
                    prevSample_ = 100.0;
                    break;
                }
            }
        }
    }

    AudioBufferQueue<double> audioBufferQueue_ {};
    std::array<double, AudioBufferQueue<double>::bufferSize> buffer_ {};
    std::size_t numCollected_ {};
    double prevSample_ = 100.0;

    static constexpr auto triggerLevel_ = 0.05;

    enum class State
    {
        waitingForTrigger,
        collecting
    };

    State state_ {State::waitingForTrigger};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscilloscopeSource)  // NOLINT
};

}  // namespace mc

#endif  // MODERN_CIRCUITS_JUCE_MODULES_MC_DSP_OSCILLOSCOPE_SOURCE_HPP
