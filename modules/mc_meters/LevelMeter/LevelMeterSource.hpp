

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
            , reduction(1.0f)
            , hold_(0)
            , rmsHistory_((size_t)rmsWindow, 0.0)
            , rmsSum_(0.0)

        {
        }

        ChannelData(const ChannelData& other)
            : max(other.max.load())
            , maxOverall(other.maxOverall.load())
            , clip(other.clip.load())
            , reduction(other.reduction.load())
            , hold_(other.hold_.load())
            , rmsHistory_(8, 0.0)
            , rmsSum_(0.0)

        {
        }

        auto operator=(const ChannelData& other) -> ChannelData&
        {
            max.store(other.max.load());
            maxOverall.store(other.maxOverall.load());
            clip.store(other.clip.load());
            reduction.store(other.reduction.load());
            hold_.store(other.hold_.load());
            rmsHistory_.resize(other.rmsHistory_.size(), 0.0);
            rmsSum_ = 0.0;
            rmsPtr_ = 0;
            return (*this);
        }

        std::atomic<float> max;
        std::atomic<float> maxOverall;
        std::atomic<bool> clip;
        std::atomic<float> reduction;

        MC_NODISCARD auto getAvgRMS() const -> float
        {
            if (!rmsHistory_.empty()) {
                auto const sum = std::accumulate(rmsHistory_.begin(), rmsHistory_.end(), 0.0);
                return static_cast<float>(std::sqrt(sum / static_cast<double>(rmsHistory_.size())));
            }

            return static_cast<float>(std::sqrt(rmsSum_));
        }

        void setLevels(const juce::int64 time, const float newMax, const float newRms, const juce::int64 newHoldMSecs)
        {
            if (newMax > 1.0 || newRms > 1.0) { clip = true; }

            maxOverall = fmaxf(maxOverall, newMax);
            if (newMax >= max) {
                max   = std::min(1.0f, newMax);
                hold_ = time + newHoldMSecs;
            } else if (time > hold_) {
                max = std::min(1.0f, newMax);
            }
            pushNextRMS(std::min(1.0f, newRms));
        }

        void setRMSsize(const size_t numBlocks)
        {
            rmsHistory_.assign(numBlocks, 0.0);
            rmsSum_ = 0.0;
            if (numBlocks > 1) {
                rmsPtr_ %= rmsHistory_.size();
            } else {
                rmsPtr_ = 0;
            }
        }

    private:
        void pushNextRMS(const float newRMS)
        {
            const double squaredRMS = std::min(newRMS * newRMS, 1.0f);
            if (!rmsHistory_.empty()) {
                rmsHistory_[(size_t)rmsPtr_] = squaredRMS;
                rmsPtr_                      = (rmsPtr_ + 1) % rmsHistory_.size();
            } else {
                rmsSum_ = squaredRMS;
            }
        }

        std::atomic<juce::int64> hold_;
        std::vector<double> rmsHistory_;
        std::atomic<double> rmsSum_;
        size_t rmsPtr_ { 0 };
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
        levels_.resize(size_t(channels), ChannelData(size_t(rmsWindow)));
        for (ChannelData& l : levels_) { l.setRMSsize(size_t(rmsWindow)); }

        newDataFlag_ = true;
    }

    /**
     Call this method to measure a block af levels to be displayed in the meters
     */
    template <typename FloatType>
    void measureBlock(const juce::AudioBuffer<FloatType>& buffer)
    {
        lastMeasurement_ = juce::Time::currentTimeMillis();
        if (!suspended_) {
            const int numChannels = buffer.getNumChannels();
            const int numSamples  = buffer.getNumSamples();

            for (int channel = 0; channel < std::min(numChannels, int(levels_.size())); ++channel) {
                levels_[size_t(channel)].setLevels(lastMeasurement_,
                    buffer.getMagnitude(channel, 0, numSamples),
                    buffer.getRMSLevel(channel, 0, numSamples),
                    holdMSecs_);
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
        for (auto& level : levels_) {
            level.setLevels(lastMeasurement_, 0.0f, 0.0f, holdMSecs_);
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
        if (juce::isPositiveAndBelow(channel, static_cast<int>(levels_.size()))) {
            levels_[size_t(channel)].reduction = reduction;
        }
    }

    /**
     With the reduction level you can add an extra bar do indicate, by what amount the level was reduced.
     This will be printed on top of the bar with half the width.
     @param reduction the factor for the reduction applied to all channels, 1.0=no reduction, 0.0=muted completely
     */
    void setReductionLevel(const float reduction)
    {
        for (auto& channel : levels_) { channel.reduction = reduction; }
    }

    /**
     Set the timeout, how long the peak line will be displayed, before it resets to the
     current peak
     */
    void setMaxHoldMS(const juce::int64 millis) { holdMSecs_ = millis; }

    /**
     Returns the reduction level. This value is not computed but can be set
     manually via \see setReductionLevel.
     */
    MC_NODISCARD auto getReductionLevel(const int channel) const -> float
    {
        if (juce::isPositiveAndBelow(channel, static_cast<int>(levels_.size()))) {
            return levels_[size_t(channel)].reduction;
        }

        return -1.0f;
    }

    /**
     This is the max level as displayed by the little line above the RMS bar.
     It is reset by \see setMaxHoldMS.
     */
    MC_NODISCARD auto getMaxLevel(const int channel) const -> float { return levels_.at(size_t(channel)).max; }

    /**
     This is the max level as displayed under the bar as number.
     It will stay up until \see clearMaxNum was called.
     */
    MC_NODISCARD auto getMaxOverallLevel(const int channel) const -> float
    {
        return levels_.at(size_t(channel)).maxOverall;
    }

    /**
     This is the RMS level that the bar will indicate. It is
     summed over rmsWindow number of blocks/measureBlock calls.
     */
    MC_NODISCARD auto getRMSLevel(const int channel) const -> float { return levels_.at(size_t(channel)).getAvgRMS(); }

    /**
     Returns the status of the clip flag.
     */
    MC_NODISCARD auto getClipFlag(const int channel) const -> bool { return levels_.at(size_t(channel)).clip; }

    /**
     Reset the clip flag to reset the indicator in the meter
     */
    void clearClipFlag(const int channel) { levels_.at(size_t(channel)).clip = false; }

    void clearAllClipFlags()
    {
        for (ChannelData& l : levels_) { l.clip = false; }
    }

    /**
     Reset the max number to minus infinity
     */
    void clearMaxNum(const int channel) { levels_.at(size_t(channel)).maxOverall = infinity; }

    /**
     Reset all max numbers
     */
    void clearAllMaxNums()
    {
        for (ChannelData& l : levels_) { l.maxOverall = infinity; }
    }

    /**
     Get the number of channels to be displayed
     */
    MC_NODISCARD auto getNumChannels() const -> int { return static_cast<int>(levels_.size()); }

    /**
     The measure can be suspended, e.g. to save CPU when no meter is displayed.
     In this case, the \see measureBlock will return immediately
     */
    void setSuspended(const bool shouldBeSuspended) { suspended_ = shouldBeSuspended; }

    MC_NODISCARD auto checkNewDataFlag() const -> bool { return newDataFlag_; }

    void resetNewDataFlag() { newDataFlag_ = false; }

private:
    JUCE_LEAK_DETECTOR(LevelMeterSource)                           // NOLINT
    juce::WeakReference<LevelMeterSource>::Master masterReference; // NOLINT(readability-identifier-naming)

    friend class juce::WeakReference<LevelMeterSource>;

    constexpr static float infinity = -100.0f;

    std::vector<ChannelData> levels_;

    juce::int64 holdMSecs_ { 500 };

    std::atomic<juce::int64> lastMeasurement_;

    bool newDataFlag_ = true;

    bool suspended_ { false };
};

/*@}*/

} // end namespace mc
