

#pragma once

namespace foleys
{

/** @addtogroup ff_meters */
/*@{*/

/**
 \class LevelMeterSource

 To get a meter GUI create a LevelMeterSource in your AudioProcessor
 or whatever instance processes an AudioBuffer.
 Then call LevelMeterSource::measureBlock (AudioBuffer<float>& buf) to
 create the readings.
 */
class LevelMeterSource
{
private:
    class ChannelData
    {
    public:
        explicit ChannelData(const size_t rmsWindow = 8)
            : max()
            , maxOverall()
            , clip(false)
            , reduction(1.0f)
            , hold_(0)
            , rmsHistory((size_t)rmsWindow, 0.0)
            , rmsSum_(0.0)

        {
        }

        ChannelData(const ChannelData& other)
            : max(other.max.load())
            , maxOverall(other.maxOverall.load())
            , clip(other.clip.load())
            , reduction(other.reduction.load())
            , hold_(other.hold_.load())
            , rmsHistory(8, 0.0)
            , rmsSum_(0.0)
            , rmsPtr(0)
        {
        }

        auto operator=(const ChannelData& other) -> ChannelData&
        {
            max.store(other.max.load());
            maxOverall.store(other.maxOverall.load());
            clip.store(other.clip.load());
            reduction.store(other.reduction.load());
            hold_.store(other.hold_.load());
            rmsHistory.resize(other.rmsHistory.size(), 0.0);
            rmsSum_ = 0.0;
            rmsPtr  = 0;
            return (*this);
        }

        std::atomic<float> max;
        std::atomic<float> maxOverall;
        std::atomic<bool> clip;
        std::atomic<float> reduction;

        [[nodiscard]] auto getAvgRMS() const -> float
        {
            if (!rmsHistory.empty())
            {
                return std::sqrt(std::accumulate(rmsHistory.begin(), rmsHistory.end(), 0.0f)
                                 / static_cast<float>(rmsHistory.size()));
            }

            return float(std::sqrt(rmsSum_));
        }

        void setLevels(const juce::int64 time, const float newMax, const float newRms, const juce::int64 newHoldMSecs)
        {
            if (newMax > 1.0 || newRms > 1.0) { clip = true; }

            maxOverall = fmaxf(maxOverall, newMax);
            if (newMax >= max)
            {
                max   = std::min(1.0f, newMax);
                hold_ = time + newHoldMSecs;
            }
            else if (time > hold_)
            {
                max = std::min(1.0f, newMax);
            }
            pushNextRMS(std::min(1.0f, newRms));
        }

        void setRMSsize(const size_t numBlocks)
        {
            rmsHistory.assign(numBlocks, 0.0);
            rmsSum_ = 0.0;
            if (numBlocks > 1) { rmsPtr %= rmsHistory.size(); }
            else
            {
                rmsPtr = 0;
            }
        }

    private:
        void pushNextRMS(const float newRMS)
        {
            const double squaredRMS = std::min(newRMS * newRMS, 1.0f);
            if (!rmsHistory.empty())
            {
                rmsHistory[(size_t)rmsPtr] = squaredRMS;
                rmsPtr                     = (rmsPtr + 1) % rmsHistory.size();
            }
            else
            {
                rmsSum_ = squaredRMS;
            }
        }

        std::atomic<juce::int64> hold_;
        std::vector<double> rmsHistory;
        std::atomic<double> rmsSum_;
        size_t rmsPtr {0};
    };

public:
    LevelMeterSource() : lastMeasurement_(0) { }

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
        levels.resize(size_t(channels), ChannelData(size_t(rmsWindow)));
        for (ChannelData& l : levels) { l.setRMSsize(size_t(rmsWindow)); }

        newDataFlag_ = true;
    }

    /**
     Call this method to measure a block af levels to be displayed in the meters
     */
    template<typename FloatType>
    void measureBlock(const juce::AudioBuffer<FloatType>& buffer)
    {
        lastMeasurement_ = juce::Time::currentTimeMillis();
        if (!suspended)
        {
            const int numChannels = buffer.getNumChannels();
            const int numSamples  = buffer.getNumSamples();

            for (int channel = 0; channel < std::min(numChannels, int(levels.size())); ++channel)
            {
                levels[size_t(channel)].setLevels(lastMeasurement_, buffer.getMagnitude(channel, 0, numSamples),
                                                  buffer.getRMSLevel(channel, 0, numSamples), holdMSecs);
            }
        }

        newDataFlag_ = true;
    }

    /**
     This is called from the GUI. If processing was stalled, this will pump zeroes into the buffer,
     until the readings return to zero.
     */
    void decayIfNeeded()
    {
        juce::int64 time = juce::Time::currentTimeMillis();
        if (time - lastMeasurement_ < 100) { return; }

        lastMeasurement_ = time;
        for (auto& level : levels)
        {
            level.setLevels(lastMeasurement_, 0.0f, 0.0f, holdMSecs);
            level.reduction = 1.0f;
        }

        newDataFlag_ = true;
    }

    /**
     With the reduction level you can add an extra bar do indicate, by what amount the level was reduced.
     This will be printed on top of the bar with half the width.
     @param channel the channel index, that was reduced
     @param reduction the factor for the reduction applied to the channel, 1.0=no reduction, 0.0=block completely
     */
    void setReductionLevel(const int channel, const float reduction)
    {
        if (juce::isPositiveAndBelow(channel, static_cast<int>(levels.size())))
        {
            levels[size_t(channel)].reduction = reduction;
        }
    }

    /**
     With the reduction level you can add an extra bar do indicate, by what amount the level was reduced.
     This will be printed on top of the bar with half the width.
     @param reduction the factor for the reduction applied to all channels, 1.0=no reduction, 0.0=muted completely
     */
    void setReductionLevel(const float reduction)
    {
        for (auto& channel : levels) { channel.reduction = reduction; }
    }

    /**
     Set the timeout, how long the peak line will be displayed, before it resets to the
     current peak
     */
    void setMaxHoldMS(const juce::int64 millis) { holdMSecs = millis; }

    /**
     Returns the reduction level. This value is not computed but can be set
     manually via \see setReductionLevel.
     */
    [[nodiscard]] auto getReductionLevel(const int channel) const -> float
    {
        if (juce::isPositiveAndBelow(channel, static_cast<int>(levels.size())))
        {
            return levels[size_t(channel)].reduction;
        }

        return -1.0f;
    }

    /**
     This is the max level as displayed by the little line above the RMS bar.
     It is reset by \see setMaxHoldMS.
     */
    [[nodiscard]] auto getMaxLevel(const int channel) const -> float { return levels.at(size_t(channel)).max; }

    /**
     This is the max level as displayed under the bar as number.
     It will stay up until \see clearMaxNum was called.
     */
    [[nodiscard]] auto getMaxOverallLevel(const int channel) const -> float
    {
        return levels.at(size_t(channel)).maxOverall;
    }

    /**
     This is the RMS level that the bar will indicate. It is
     summed over rmsWindow number of blocks/measureBlock calls.
     */
    [[nodiscard]] auto getRMSLevel(const int channel) const -> float { return levels.at(size_t(channel)).getAvgRMS(); }

    /**
     Returns the status of the clip flag.
     */
    [[nodiscard]] auto getClipFlag(const int channel) const -> bool { return levels.at(size_t(channel)).clip; }

    /**
     Reset the clip flag to reset the indicator in the meter
     */
    void clearClipFlag(const int channel) { levels.at(size_t(channel)).clip = false; }

    void clearAllClipFlags()
    {
        for (ChannelData& l : levels) { l.clip = false; }
    }

    /**
     Reset the max number to minus infinity
     */
    void clearMaxNum(const int channel) { levels.at(size_t(channel)).maxOverall = infinity; }

    /**
     Reset all max numbers
     */
    void clearAllMaxNums()
    {
        for (ChannelData& l : levels) { l.maxOverall = infinity; }
    }

    /**
     Get the number of channels to be displayed
     */
    [[nodiscard]] auto getNumChannels() const -> int { return static_cast<int>(levels.size()); }

    /**
     The measure can be suspended, e.g. to save CPU when no meter is displayed.
     In this case, the \see measureBlock will return immediately
     */
    void setSuspended(const bool shouldBeSuspended) { suspended = shouldBeSuspended; }

    [[nodiscard]] auto checkNewDataFlag() const -> bool { return newDataFlag_; }

    void resetNewDataFlag() { newDataFlag_ = false; }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LevelMeterSource)  // NOLINT
    juce::WeakReference<LevelMeterSource>::Master masterReference;
    friend class juce::WeakReference<LevelMeterSource>;

    constexpr static float infinity = -100.0f;

    std::vector<ChannelData> levels;

    juce::int64 holdMSecs {500};

    std::atomic<juce::int64> lastMeasurement_;

    bool newDataFlag_ = true;

    bool suspended {false};
};

/*@}*/

}  // end namespace foleys
