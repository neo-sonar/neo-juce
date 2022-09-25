

#pragma once

namespace mc {

/// To get a meter GUI create a LevelMeterSource in your AudioProcessor
/// or whatever instance processes an AudioBuffer.
/// Then call LevelMeterSource::measureBlock (AudioBuffer<float>& buf) to
/// create the readings.
struct LevelMeterSource {
private:
    struct ChannelData {
        explicit ChannelData(const size_t rmsWindow = 8)
            : max()
            , maxOverall()
            , clip(false)
            , reduction(1.0F)
            , _hold(0)
            , _rmsHistory((size_t)rmsWindow, 0.0)
            , _rmsSum(0.0)

        {
        }

        ChannelData(const ChannelData& other)
            : max(other.max.load())
            , maxOverall(other.maxOverall.load())
            , clip(other.clip.load())
            , reduction(other.reduction.load())
            , _hold(other._hold.load())
            , _rmsHistory(8, 0.0)
            , _rmsSum(0.0)

        {
        }

        auto operator=(const ChannelData& other) -> ChannelData&
        {
            max.store(other.max.load());
            maxOverall.store(other.maxOverall.load());
            clip.store(other.clip.load());
            reduction.store(other.reduction.load());
            _hold.store(other._hold.load());
            _rmsHistory.resize(other._rmsHistory.size(), 0.0);
            _rmsSum = 0.0;
            _rmsPtr = 0;
            return (*this);
        }

        Atomic<float> max;
        Atomic<float> maxOverall;
        Atomic<bool> clip;
        Atomic<float> reduction;

        [[nodiscard]] auto getAvgRMS() const -> float
        {
            if (!_rmsHistory.empty()) {
                auto const sum = std::accumulate(_rmsHistory.begin(), _rmsHistory.end(), 0.0);
                return static_cast<float>(std::sqrt(sum / static_cast<double>(_rmsHistory.size())));
            }

            return static_cast<float>(std::sqrt(_rmsSum));
        }

        void setLevels(const juce::int64 time, const float newMax, const float newRms, const juce::int64 newHoldMSecs)
        {
            if (newMax > 1.0 || newRms > 1.0) { clip = true; }

            maxOverall = fmaxf(maxOverall, newMax);
            if (newMax >= max) {
                max   = std::min(1.0F, newMax);
                _hold = time + newHoldMSecs;
            } else if (time > _hold) {
                max = std::min(1.0F, newMax);
            }
            pushNextRMS(std::min(1.0F, newRms));
        }

        void setRMSsize(const size_t numBlocks)
        {
            _rmsHistory.assign(numBlocks, 0.0);
            _rmsSum = 0.0;
            if (numBlocks > 1) {
                _rmsPtr %= _rmsHistory.size();
            } else {
                _rmsPtr = 0;
            }
        }

    private:
        void pushNextRMS(const float newRMS)
        {
            const double squaredRMS = std::min(newRMS * newRMS, 1.0F);
            if (!_rmsHistory.empty()) {
                _rmsHistory[(size_t)_rmsPtr] = squaredRMS;
                _rmsPtr                      = (_rmsPtr + 1) % _rmsHistory.size();
            } else {
                _rmsSum = squaredRMS;
            }
        }

        Atomic<juce::int64> _hold;
        Vector<double> _rmsHistory;
        Atomic<double> _rmsSum;
        size_t _rmsPtr { 0 };
    };

public:
    LevelMeterSource() : _lastMeasurement(0) { }

    ~LevelMeterSource() { masterReference.clear(); }

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
    void resize(const int channels, const int rmsWindow)
    {
        _levels.resize(size_t(channels), ChannelData(size_t(rmsWindow)));
        for (ChannelData& l : _levels) { l.setRMSsize(size_t(rmsWindow)); }

        _newDataFlag = true;
    }

    /**
     Call this method to measure a block af levels to be displayed in the meters
     */
    template <typename FloatType>
    void measureBlock(const juce::AudioBuffer<FloatType>& buffer)
    {
        _lastMeasurement = juce::Time::currentTimeMillis();
        if (!_suspended) {
            const int numChannels = buffer.getNumChannels();
            const int numSamples  = buffer.getNumSamples();

            for (int channel = 0; channel < std::min(numChannels, int(_levels.size())); ++channel) {
                _levels[size_t(channel)].setLevels(_lastMeasurement,
                    buffer.getMagnitude(channel, 0, numSamples),
                    buffer.getRMSLevel(channel, 0, numSamples),
                    _holdMSecs);
            }
        }

        _newDataFlag = true;
    }

    /**
     This is called from the GUI. If processing was stalled, this will pump zeroes into the buffer,
     until the readings return to zero.
     */
    void decayIfNeeded()
    {
        juce::int64 const time = juce::Time::currentTimeMillis();
        if (time - _lastMeasurement < 100) { return; }

        _lastMeasurement = time;
        for (auto& level : _levels) {
            level.setLevels(_lastMeasurement, 0.0F, 0.0F, _holdMSecs);
            level.reduction = 1.0F;
        }

        _newDataFlag = true;
    }

    /**
     With the reduction level you can add an extra bar do indicate, by what amount the level was reduced.
     This will be printed on top of the bar with half the width.
     @param channel the channel index, that was reduced
     @param reduction the factor for the reduction applied to the channel, 1.0=no reduction, 0.0=block completely
     */
    void setReductionLevel(const int channel, const float reduction)
    {
        if (juce::isPositiveAndBelow(channel, static_cast<int>(_levels.size()))) {
            _levels[size_t(channel)].reduction = reduction;
        }
    }

    /**
     With the reduction level you can add an extra bar do indicate, by what amount the level was reduced.
     This will be printed on top of the bar with half the width.
     @param reduction the factor for the reduction applied to all channels, 1.0=no reduction, 0.0=muted completely
     */
    void setReductionLevel(const float reduction)
    {
        for (auto& channel : _levels) { channel.reduction = reduction; }
    }

    /**
     Set the timeout, how long the peak line will be displayed, before it resets to the
     current peak
     */
    void setMaxHoldMS(const juce::int64 millis) { _holdMSecs = millis; }

    /**
     Returns the reduction level. This value is not computed but can be set
     manually via \see setReductionLevel.
     */
    [[nodiscard]] auto getReductionLevel(const int channel) const -> float
    {
        if (juce::isPositiveAndBelow(channel, static_cast<int>(_levels.size()))) {
            return _levels[size_t(channel)].reduction;
        }

        return -1.0F;
    }

    /**
     This is the max level as displayed by the little line above the RMS bar.
     It is reset by \see setMaxHoldMS.
     */
    [[nodiscard]] auto getMaxLevel(const int channel) const -> float { return _levels.at(size_t(channel)).max; }

    /**
     This is the max level as displayed under the bar as number.
     It will stay up until \see clearMaxNum was called.
     */
    [[nodiscard]] auto getMaxOverallLevel(const int channel) const -> float
    {
        return _levels.at(size_t(channel)).maxOverall;
    }

    /**
     This is the RMS level that the bar will indicate. It is
     summed over rmsWindow number of blocks/measureBlock calls.
     */
    [[nodiscard]] auto getRMSLevel(const int channel) const -> float { return _levels.at(size_t(channel)).getAvgRMS(); }

    /**
     Returns the status of the clip flag.
     */
    [[nodiscard]] auto getClipFlag(const int channel) const -> bool { return _levels.at(size_t(channel)).clip; }

    /**
     Reset the clip flag to reset the indicator in the meter
     */
    void clearClipFlag(const int channel) { _levels.at(size_t(channel)).clip = false; }

    void clearAllClipFlags()
    {
        for (ChannelData& l : _levels) { l.clip = false; }
    }

    /**
     Reset the max number to minus infinity
     */
    void clearMaxNum(const int channel) { _levels.at(size_t(channel)).maxOverall = infinity; }

    /**
     Reset all max numbers
     */
    void clearAllMaxNums()
    {
        for (ChannelData& l : _levels) { l.maxOverall = infinity; }
    }

    /**
     Get the number of channels to be displayed
     */
    [[nodiscard]] auto getNumChannels() const -> int { return static_cast<int>(_levels.size()); }

    /**
     The measure can be suspended, e.g. to save CPU when no meter is displayed.
     In this case, the \see measureBlock will return immediately
     */
    void setSuspended(const bool shouldBeSuspended) { _suspended = shouldBeSuspended; }

    [[nodiscard]] auto checkNewDataFlag() const -> bool { return _newDataFlag; }

    void resetNewDataFlag() { _newDataFlag = false; }

private:
    JUCE_LEAK_DETECTOR(LevelMeterSource)                           // NOLINT
    juce::WeakReference<LevelMeterSource>::Master masterReference; // NOLINT(readability-identifier-naming)

    friend class juce::WeakReference<LevelMeterSource>;

    constexpr static float infinity = -100.0F;

    Vector<ChannelData> _levels;

    juce::int64 _holdMSecs { 500 };

    Atomic<juce::int64> _lastMeasurement;

    bool _newDataFlag = true;

    bool _suspended { false };
};

/*@}*/

} // end namespace mc
