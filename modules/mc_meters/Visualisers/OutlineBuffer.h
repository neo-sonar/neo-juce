
#pragma once

namespace mc {

/** @addtogroup ff_meters */
/*@{*/

/**
 \class OutlineBuffer

 This class implements a circular buffer to store min and max values
 of anaudio signal. The block size can be specified. At any time the
 UI can request an outline of the last n blocks as Path to fill or stroke
 */
class OutlineBuffer {

    class ChannelData {
        std::vector<float> minBuffer_;
        std::vector<float> maxBuffer_;
        std::atomic<size_t> writePointer_ { 0 };
        int fraction_        = 0;
        int samplesPerBlock_ = 128;

        JUCE_LEAK_DETECTOR(ChannelData) // NOLINT
    public:
        ChannelData() { setSize(1024); }

        /**
         This copy constructor does not really copy. It is only present to satisfy the vector.
         */
        ChannelData(const ChannelData& other) { setSize(other.getSize()); }

        /**
         @return the number of values the buffer will store.
         */
        MC_NODISCARD auto getSize() const -> int { return static_cast<int>(minBuffer_.size()); }

        void setSamplesPerBlock(const int numSamples) { samplesPerBlock_ = numSamples; }

        /**
         @param numBlocks is the number of values the buffer will store. Allow a little safety buffer, so you
         don't write into the part, where it is currently read
         */
        void setSize(const int numBlocks)
        {
            minBuffer_.resize(size_t(numBlocks), 0.0f);
            maxBuffer_.resize(size_t(numBlocks), 0.0f);
            writePointer_ = writePointer_ % size_t(numBlocks);
        }

        void pushChannelData(const float* input, const int numSamples)
        {
            // create peak values
            int samples = 0;
            juce::Range<float> minMax;
            while (samples < numSamples) {
                auto leftover = numSamples - samples;
                if (fraction_ > 0) {
                    minMax                            = juce::FloatVectorOperations::findMinAndMax(input, samplesPerBlock_ - fraction_);
                    maxBuffer_[(size_t)writePointer_] = std::max(maxBuffer_[(size_t)writePointer_], minMax.getEnd());
                    minBuffer_[(size_t)writePointer_] = std::min(minBuffer_[(size_t)writePointer_], minMax.getStart());
                    samples += samplesPerBlock_ - fraction_;
                    fraction_     = 0;
                    writePointer_ = (writePointer_ + 1) % maxBuffer_.size();
                } else if (leftover > samplesPerBlock_) {
                    minMax                            = juce::FloatVectorOperations::findMinAndMax(input + samples, samplesPerBlock_);
                    maxBuffer_[(size_t)writePointer_] = minMax.getEnd();
                    minBuffer_[(size_t)writePointer_] = minMax.getStart();
                    samples += samplesPerBlock_;
                    writePointer_ = (writePointer_ + 1) % maxBuffer_.size();
                } else {
                    minMax                            = juce::FloatVectorOperations::findMinAndMax(input + samples, leftover);
                    maxBuffer_[(size_t)writePointer_] = minMax.getEnd();
                    minBuffer_[(size_t)writePointer_] = minMax.getStart();
                    samples += samplesPerBlock_ - fraction_;
                    fraction_ = leftover;
                }
                jassert(minMax.getStart() == minMax.getStart() && minMax.getEnd() == minMax.getEnd());
            }
        }

        void getChannelOutline(juce::Path& outline, const juce::Rectangle<float> bounds,
            const int numSamplesToPlot) const
        {
            auto numSamples = size_t(numSamplesToPlot);
            auto latest     = writePointer_ > 0 ? writePointer_ - 1 : maxBuffer_.size() - 1;
            auto oldest     = (latest >= numSamples) ? latest - numSamples : latest + maxBuffer_.size() - numSamples;

            const auto dx = bounds.getWidth() / static_cast<float>(numSamples);
            const auto dy = bounds.getHeight() * 0.35f;
            const auto my = bounds.getCentreY();
            auto x        = bounds.getX();
            auto s        = oldest;

            outline.startNewSubPath(x, my);
            for (size_t i = 0; i < numSamples; ++i) {
                outline.lineTo(x, my + minBuffer_[s] * dy);
                x += dx;
                if (s < minBuffer_.size() - 1) {
                    s += 1;
                } else {
                    s = 0;
                }
            }

            for (size_t i = 0; i < numSamples; ++i) {
                outline.lineTo(x, my + maxBuffer_[s] * dy);
                x -= dx;
                if (s > 1) {
                    s -= 1;
                } else {
                    s = maxBuffer_.size() - 1;
                }
            }
        }
    };

    std::vector<ChannelData> channelDatas_;
    int samplesPerBlock_ = 128;

    JUCE_LEAK_DETECTOR(OutlineBuffer) // NOLINT
public:
    OutlineBuffer() = default;

    /**
     @param numChannels is the number of channels the buffer will store
     @param numBlocks is the number of values the buffer will store. Allow a little safety buffer, so you
     don't write into the part, where it is currently read
     */
    void setSize(const int numChannels, const int numBlocks)
    {
        channelDatas_.resize(size_t(numChannels));
        for (auto& data : channelDatas_) {
            data.setSize(numBlocks);
            data.setSamplesPerBlock(samplesPerBlock_);
        }
    }

    /**
     @param numSamples sets the size of each analysed block
     */
    void setSamplesPerBlock(const int numSamples)
    {
        samplesPerBlock_ = numSamples;
        for (auto& data : channelDatas_) {
            data.setSamplesPerBlock(numSamples);
        }
    }

    /**
     Push a block of audio samples into the outline buffer.
     */
    void pushBlock(const juce::AudioBuffer<float>& buffer, const int numSamples)
    {
        for (int i = 0; i < buffer.getNumChannels(); ++i) {
            if (i < int(channelDatas_.size())) {
                channelDatas_[size_t(i)].pushChannelData(buffer.getReadPointer(i), numSamples);
            }
        }
    }

    /**
     Returns the outline of a specific channel inside the bounds.
     @param path is a Path to be populated
     @param bounds the rectangle to paint within. The result is not clipped, if samples are exceeding 1.0, it may paint
     outside
     @param channel the index of the channel to paint
     @param numSamples is the number of sample blocks
     @return a path with a single channel outline (min to max)
     */
    void getChannelOutline(juce::Path& path, const juce::Rectangle<float> bounds, const int channel,
        const int numSamples) const
    {
        if (channel < int(channelDatas_.size())) {
            return channelDatas_[size_t(channel)].getChannelOutline(path, bounds, numSamples);
        }
    }

    /**
     This returns the outlines of each channel, splitting the bounds into equal sized rows
     @param path is a Path to be populated
     @param bounds the rectangle to paint within. The result is not clipped, if samples are exceeding 1.0, it may paint
     outside
     @param numSamples is the number of sample blocks
     @return a path with a single channel outline (min to max)
     */
    void getChannelOutline(juce::Path& path, const juce::Rectangle<float> bounds, const int numSamples) const
    {
        juce::Rectangle<float> b(bounds);
        auto const numChannels = static_cast<int>(channelDatas_.size());
        auto const h           = bounds.getHeight() / static_cast<float>(numChannels);
        for (int i = 0; i < numChannels; ++i) {
            getChannelOutline(path, b.removeFromTop(h), i, numSamples);
        }
    }
};
/*@}*/
} // namespace mc
