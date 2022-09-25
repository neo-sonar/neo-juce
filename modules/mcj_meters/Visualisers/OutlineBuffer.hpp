
#pragma once

namespace mc {

/// This class implements a circular buffer to store min and max values
/// of anaudio signal. The block size can be specified. At any time the
/// UI can request an outline of the last n blocks as Path to fill or stroke
struct OutlineBuffer {
private:
    struct ChannelData {
    private:
        Vector<float> _minBuffer;
        Vector<float> _maxBuffer;
        Atomic<size_t> _writePointer { 0 };
        int _fraction        = 0;
        int _samplesPerBlock = 128;

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
        [[nodiscard]] auto getSize() const -> int { return static_cast<int>(_minBuffer.size()); }

        void setSamplesPerBlock(const int numSamples) { _samplesPerBlock = numSamples; }

        /**
         @param numBlocks is the number of values the buffer will store. Allow a little safety buffer, so you
         don't write into the part, where it is currently read
         */
        void setSize(const int numBlocks)
        {
            _minBuffer.resize(size_t(numBlocks), 0.0F);
            _maxBuffer.resize(size_t(numBlocks), 0.0F);
            _writePointer = _writePointer % size_t(numBlocks);
        }

        void pushChannelData(const float* input, const int numSamples)
        {
            // create peak values
            int samples = 0;
            juce::Range<float> minMax;
            while (samples < numSamples) {
                auto leftover = numSamples - samples;
                if (_fraction > 0) {
                    minMax = juce::FloatVectorOperations::findMinAndMax(input, _samplesPerBlock - _fraction);
                    _maxBuffer[(size_t)_writePointer] = std::max(_maxBuffer[(size_t)_writePointer], minMax.getEnd());
                    _minBuffer[(size_t)_writePointer] = std::min(_minBuffer[(size_t)_writePointer], minMax.getStart());
                    samples += _samplesPerBlock - _fraction;
                    _fraction     = 0;
                    _writePointer = (_writePointer + 1) % _maxBuffer.size();
                } else if (leftover > _samplesPerBlock) {
                    minMax = juce::FloatVectorOperations::findMinAndMax(input + samples, _samplesPerBlock);
                    _maxBuffer[(size_t)_writePointer] = minMax.getEnd();
                    _minBuffer[(size_t)_writePointer] = minMax.getStart();
                    samples += _samplesPerBlock;
                    _writePointer = (_writePointer + 1) % _maxBuffer.size();
                } else {
                    minMax = juce::FloatVectorOperations::findMinAndMax(input + samples, leftover);
                    _maxBuffer[(size_t)_writePointer] = minMax.getEnd();
                    _minBuffer[(size_t)_writePointer] = minMax.getStart();
                    samples += _samplesPerBlock - _fraction;
                    _fraction = leftover;
                }
                jassert(minMax.getStart() == minMax.getStart() && minMax.getEnd() == minMax.getEnd());
            }
        }

        void
        getChannelOutline(juce::Path& outline, const juce::Rectangle<float> bounds, const int numSamplesToPlot) const
        {
            auto numSamples = size_t(numSamplesToPlot);
            auto latest     = _writePointer > 0 ? _writePointer - 1 : _maxBuffer.size() - 1;
            auto oldest     = (latest >= numSamples) ? latest - numSamples : latest + _maxBuffer.size() - numSamples;

            const auto dx = bounds.getWidth() / static_cast<float>(numSamples);
            const auto dy = bounds.getHeight() * 0.35F;
            const auto my = bounds.getCentreY();
            auto x        = bounds.getX();
            auto s        = oldest;

            outline.startNewSubPath(x, my);
            for (size_t i = 0; i < numSamples; ++i) {
                outline.lineTo(x, my + _minBuffer[s] * dy);
                x += dx;
                if (s < _minBuffer.size() - 1) {
                    s += 1;
                } else {
                    s = 0;
                }
            }

            for (size_t i = 0; i < numSamples; ++i) {
                outline.lineTo(x, my + _maxBuffer[s] * dy);
                x -= dx;
                if (s > 1) {
                    s -= 1;
                } else {
                    s = _maxBuffer.size() - 1;
                }
            }
        }
    };

    Vector<ChannelData> _channelDatas;
    int _samplesPerBlock = 128;

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
        _channelDatas.resize(size_t(numChannels));
        for (auto& data : _channelDatas) {
            data.setSize(numBlocks);
            data.setSamplesPerBlock(_samplesPerBlock);
        }
    }

    /**
     @param numSamples sets the size of each analysed block
     */
    void setSamplesPerBlock(const int numSamples)
    {
        _samplesPerBlock = numSamples;
        for (auto& data : _channelDatas) { data.setSamplesPerBlock(numSamples); }
    }

    /**
     Push a block of audio samples into the outline buffer.
     */
    void pushBlock(const juce::AudioBuffer<float>& buffer, const int numSamples)
    {
        for (int i = 0; i < buffer.getNumChannels(); ++i) {
            if (i < int(_channelDatas.size())) {
                _channelDatas[size_t(i)].pushChannelData(buffer.getReadPointer(i), numSamples);
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
    void getChannelOutline(juce::Path& path,
        const juce::Rectangle<float> bounds,
        const int channel,
        const int numSamples) const
    {
        if (channel < int(_channelDatas.size())) {
            return _channelDatas[size_t(channel)].getChannelOutline(path, bounds, numSamples);
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
        auto const numChannels = static_cast<int>(_channelDatas.size());
        auto const h           = bounds.getHeight() / static_cast<float>(numChannels);
        for (int i = 0; i < numChannels; ++i) { getChannelOutline(path, b.removeFromTop(h), i, numSamples); }
    }
};
/*@}*/
} // namespace mc
