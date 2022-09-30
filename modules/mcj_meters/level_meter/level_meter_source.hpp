#pragma once

namespace mc {

/// To get a meter GUI create a LevelMeterSource in your AudioProcessor
/// or whatever instance processes an AudioBuffer.
/// Then call LevelMeterSource::measureBlock (AudioBuffer<float>& buf) to
/// create the readings.
struct LevelMeterSource {
private:
    struct ChannelData {
        explicit ChannelData(const size_t rmsWindow = 8);

        ChannelData(ChannelData const& other);
        auto operator=(ChannelData const& other) -> ChannelData&;

        [[nodiscard]] auto getAvgRMS() const -> float;
        void setLevels(const juce::int64 time, float const newMax, float const newRms, const juce::int64 newHoldMSecs);
        void setRMSsize(const size_t numBlocks);

        Atomic<float> max;
        Atomic<float> maxOverall;
        Atomic<bool> clip;
        Atomic<float> reduction;

    private:
        void pushNextRMS(float const newRMS);

        Atomic<juce::int64> _hold;
        Vector<double> _rmsHistory;
        Atomic<double> _rmsSum;
        size_t _rmsPtr { 0 };
    };

public:
    LevelMeterSource();
    ~LevelMeterSource();

    /**
     Resize the meters data containers. Set the
     \param numChannels to the number of channels. If you don't do this in prepareToPlay,
            it will be done when calling measureBlock, but a few bytes will be allocated
            on the audio thread, so be aware.
     \param rmsWindow is the number of rms values to gather. Keep that aligned with
            the sampleRate and the blocksize to get reproducable results.
            e.g. `rmsWindow = msecs * 0.001f * sampleRate / blockSize;`
     \FIXME: don't call this when measureBlock is processing
     */
    void resize(int const channels, int const rmsWindow);

    /**
     Call this method to measure a block af levels to be displayed in the meters
     */
    template <typename FloatType>
    void measureBlock(juce::AudioBuffer<FloatType> const& buffer);

    /**
     This is called from the GUI. If processing was stalled, this will pump zeroes into the buffer,
     until the readings return to zero.
     */
    void decayIfNeeded();

    /**
     With the reduction level you can add an extra bar do indicate, by what amount the level was reduced.
     This will be printed on top of the bar with half the width.
     @param channel the channel index, that was reduced
     @param reduction the factor for the reduction applied to the channel, 1.0=no reduction, 0.0=block completely
     */
    void setReductionLevel(int const channel, float const reduction);

    /**
     With the reduction level you can add an extra bar do indicate, by what amount the level was reduced.
     This will be printed on top of the bar with half the width.
     @param reduction the factor for the reduction applied to all channels, 1.0=no reduction, 0.0=muted completely
     */
    void setReductionLevel(float const reduction);

    /**
     Set the timeout, how long the peak line will be displayed, before it resets to the
     current peak
     */
    void setMaxHoldMS(const juce::int64 millis);

    /**
     Returns the reduction level. This value is not computed but can be set
     manually via \see setReductionLevel.
     */
    [[nodiscard]] auto getReductionLevel(int const channel) const -> float;

    /**
     This is the max level as displayed by the little line above the RMS bar.
     It is reset by \see setMaxHoldMS.
     */
    [[nodiscard]] auto getMaxLevel(int const channel) const -> float;

    /**
     This is the max level as displayed under the bar as number.
     It will stay up until \see clearMaxNum was called.
     */
    [[nodiscard]] auto getMaxOverallLevel(int const channel) const -> float;

    /**
     This is the RMS level that the bar will indicate. It is
     summed over rmsWindow number of blocks/measureBlock calls.
     */
    [[nodiscard]] auto getRMSLevel(int const channel) const -> float;

    /**
     Returns the status of the clip flag.
     */
    [[nodiscard]] auto getClipFlag(int const channel) const -> bool;

    /**
     Reset the clip flag to reset the indicator in the meter
     */
    void clearClipFlag(int const channel);
    void clearAllClipFlags();

    /**
     Reset the max number to minus infinity
     */
    void clearMaxNum(int const channel);

    /**
     Reset all max numbers
     */
    void clearAllMaxNums();

    /**
     Get the number of channels to be displayed
     */
    [[nodiscard]] auto getNumChannels() const -> int;

    /**
     The measure can be suspended, e.g. to save CPU when no meter is displayed.
     In this case, the \see measureBlock will return immediately
     */
    void setSuspended(bool const shouldBeSuspended);

    [[nodiscard]] auto checkNewDataFlag() const -> bool;

    void resetNewDataFlag();

private:
    JUCE_LEAK_DETECTOR(LevelMeterSource)                           // NOLINT
    juce::WeakReference<LevelMeterSource>::Master masterReference; // NOLINT(readability-identifier-naming)

    friend class juce::WeakReference<LevelMeterSource>;

    static constexpr float infinity = -100.0F;

    Vector<ChannelData> _levels;
    juce::int64 _holdMSecs { 500 };
    Atomic<juce::int64> _lastMeasurement;
    bool _newDataFlag = true;
    bool _suspended { false };
};

/*@}*/

template <typename FloatType>
void LevelMeterSource::measureBlock(juce::AudioBuffer<FloatType> const& buffer)
{
    _lastMeasurement = juce::Time::currentTimeMillis();
    if (!_suspended) {
        int const numChannels = buffer.getNumChannels();
        int const numSamples  = buffer.getNumSamples();

        for (int channel = 0; channel < std::min(numChannels, int(_levels.size())); ++channel) {
            _levels[size_t(channel)].setLevels(_lastMeasurement,
                buffer.getMagnitude(channel, 0, numSamples),
                buffer.getRMSLevel(channel, 0, numSamples),
                _holdMSecs);
        }
    }

    _newDataFlag = true;
}

} // end namespace mc
