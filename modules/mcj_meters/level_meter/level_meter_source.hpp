#pragma once

namespace mc {

/// To get a meter GUI create a LevelMeterSource in your AudioProcessor
/// or whatever instance processes an AudioBuffer.
/// Then call LevelMeterSource::measureBlock (AudioBuffer<float>& buf) to
/// create the readings.
struct LevelMeterSource {
    LevelMeterSource();
    ~LevelMeterSource();

    ///  \brief Resize the meters data containers. Set the
    ///
    ///  \param numChannels to the number of channels. If you don't
    ///         do this in prepareToPlay, it will be done when calling measureBlock,
    ///         but a few bytes will be allocated on the audio thread, so be aware.
    ///
    ///  \param rmsWindow is the number of rms values to gather. Keep that aligned with
    ///         the sampleRate and the blocksize to get reproducable results.
    ///         e.g. `rmsWindow = msecs * 0.001f * sampleRate / blockSize;`
    auto resize(int channels, int rmsWindow) -> void;

    /// \brief Call this method to measure a block af levels to be displayed in the meters.
    template <typename FloatType>
    auto measureBlock(juce::AudioBuffer<FloatType> const& buffer) -> void;

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
     With the reduction level you can add an extra bar do indicate, by what amount the level was reduced.
     This will be printed on top of the bar with half the width.
     @param reduction the factor for the reduction applied to all channels, 1.0=no reduction, 0.0=muted completely
     */
    auto reductionLevel(float reduction) -> void;

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

template <typename FloatType>
void LevelMeterSource::measureBlock(juce::AudioBuffer<FloatType> const& buffer)
{
    _lastMeasurement = juce::Time::currentTimeMillis();
    if (!_suspended) {
        int const numChannels = buffer.getNumChannels();
        int const numSamples  = buffer.getNumSamples();

        for (int channel = 0; channel < std::min(numChannels, int(_levels.size())); ++channel) {
            _levels[size_t(channel)].levels(_lastMeasurement,
                buffer.getMagnitude(channel, 0, numSamples),
                buffer.rmsLevel(channel, 0, numSamples),
                _holdMSecs);
        }
    }

    _newDataFlag = true;
}

} // end namespace mc
