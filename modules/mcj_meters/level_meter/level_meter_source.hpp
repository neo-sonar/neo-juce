#pragma once

namespace mc {

/// To get a meter GUI create a LevelMeterSource in your AudioProcessor
/// or whatever instance processes an AudioBuffer.
/// Then call LevelMeterSource::measureBlock (AudioBuffer<float>& buf) to
/// create the readings.
struct LevelMeterSource {
    LevelMeterSource();
    ~LevelMeterSource();

    /// \brief Set's the window size of rms measurements.
    auto rmsWindow(Milliseconds<int> millis) -> void;

    /// \brief Needs to called before any processing.
    auto prepare(juce::dsp::ProcessSpec const& spec) -> void;

    /// \brief Call this method to measure a block af levels to be displayed in the meters.
    template <typename ProcessContext>
    auto process(ProcessContext const& context) -> void;

    /// \brief Call this method to measure a block af levels to be displayed in the meters.
    template <typename FloatType>
    auto measureBlock(juce::AudioBuffer<FloatType> const& buffer) -> void;

    /// @brief Clears all levels & clip flags.
    auto reset() -> void;

    /// \brief This is called from the GUI. If processing was stalled,
    // this will pump zeroes into the buffer, until the readings return to zero.
    auto decayIfNeeded() -> void;

    /**
     With the reduction level you can add an extra bar do indicate, by what amount the level was reduced.
     This will be printed on top of the bar with half the width.
     @param channel the channel index, that was reduced
     @param reduction the factor for the reduction applied to the channel, 1.0=no reduction, 0.0=block completely
     */
    auto reductionLevel(int channel, float reduction) -> void;

    /**
     Set the timeout, how long the peak line will be displayed, before it resets to the
     current peak
     */
    auto setMaxHoldMS(juce::int64 millis) -> void;

    /**
     Returns the reduction level. This value is not computed but can be set
     manually via \see reductionLevel.
     */
    [[nodiscard]] auto reductionLevel(int channel) const -> float;

    /**
     This is the max level as displayed by the little line above the RMS bar.
     It is reset by \see setMaxHoldMS.
     */
    [[nodiscard]] auto maxLevel(int channel) const -> float;

    /**
     This is the max level as displayed under the bar as number.
     It will stay up until \see clearMaxNum was called.
     */
    [[nodiscard]] auto maxOverallLevel(int channel) const -> float;

    /**
     This is the RMS level that the bar will indicate. It is
     summed over rmsWindow number of blocks/measureBlock calls.
     */
    [[nodiscard]] auto rmsLevel(int channel) const -> float;

    /**
     Returns the status of the clip flag.
     */
    [[nodiscard]] auto clipFlag(int channel) const -> bool;

    /**
     Reset the clip flag to reset the indicator in the meter
     */
    auto clearClipFlag(int channel) -> void;
    auto clearAllClipFlags() -> void;

    /**
     Reset the max number to minus infinity
     */
    auto clearMaxNum(int channel) -> void;

    /**
     Reset all max numbers
     */
    auto clearAllMaxNums() -> void;

    /**
     Get the number of channels to be displayed
     */
    [[nodiscard]] auto numChannels() const -> int;

    /**
     The measure can be suspended, e.g. to save CPU when no meter is displayed.
     In this case, the \see measureBlock will return immediately
     */
    auto setSuspended(bool shouldBeSuspended) -> void;

    [[nodiscard]] auto checkNewDataFlag() const -> bool;

    auto resetNewDataFlag() -> void;

private:
    struct ChannelData {
        explicit ChannelData(size_t rmsWindow = 8);

        ChannelData(ChannelData const& other);
        auto operator=(ChannelData const& other) -> ChannelData&;

        [[nodiscard]] auto rmsAverage() const -> float;
        auto levels(juce::int64 time, float newMax, float newRms, juce::int64 newHoldMSecs) -> void;
        auto rmsSize(size_t numBlocks) -> void;

        Atomic<float> max;
        Atomic<float> maxOverall;
        Atomic<bool> clip;
        Atomic<float> reduction;

    private:
        auto pushRMS(float newRMS) -> void;

        Atomic<juce::int64> _hold;
        Vector<double> _rmsHistory;
        Atomic<double> _rmsSum;
        size_t _rmsPtr { 0 };
    };

    template <typename FloatType>
    auto processInternal(juce::dsp::AudioBlock<FloatType const> block) -> void;

    JUCE_LEAK_DETECTOR(LevelMeterSource)                           // NOLINT
    juce::WeakReference<LevelMeterSource>::Master masterReference; // NOLINT(readability-identifier-naming)

    friend class juce::WeakReference<LevelMeterSource>;

    static constexpr float infinity = -100.0F;

    Vector<ChannelData> _levels;
    juce::int64 _holdMSecs { 500 };
    Atomic<juce::int64> _lastMeasurement;
    Seconds<float> _rmsWindow { 300 };
    bool _newDataFlag = true;
    bool _suspended { false };
};

template <typename FloatType>
void LevelMeterSource::measureBlock(juce::AudioBuffer<FloatType> const& buffer)
{
    processInternal(juce::dsp::AudioBlock<FloatType const> { buffer });
}

template <typename ProcessContext>
auto LevelMeterSource::process(ProcessContext const& context) -> void
{
    auto inBlock  = context.getInputBlock();
    auto outBlock = context.getOutputBlock();
    if (ProcessContext::usesSeparateInputAndOutputBlocks()) { outBlock.copyFrom(inBlock); }
    processInternal(outBlock);
}

template <typename FloatType>
auto LevelMeterSource::processInternal(juce::dsp::AudioBlock<FloatType const> block) -> void
{
    _lastMeasurement = juce::Time::currentTimeMillis();
    if (!_suspended) {
        auto const numChannels = block.getNumChannels();
        for (size_t i { 0 }; i < std::min(numChannels, _levels.size()); ++i) {
            auto const channel = block.getSingleChannelBlock(i);
            auto const mag     = channel.findMinAndMax().getEnd();
            auto const rms     = mc::rmsLevel(channel);
            _levels[i].levels(_lastMeasurement, mag, rms, _holdMSecs);
        }
    }
    _newDataFlag = true;
}

} // end namespace mc
