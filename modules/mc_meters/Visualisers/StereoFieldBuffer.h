
#pragma once

namespace mc {

/** @addtogroup ff_meters */
/*@{*/

/**
 \class StereoFieldBuffer

 This class implements a circular buffer to buffer audio samples.
 At any time the GUI can ask for a stereo field visualisation of
 two neightbouring channels.
 */
template <typename FloatType>
class StereoFieldBuffer {
    juce::AudioBuffer<FloatType> sampleBuffer_;
    std::atomic<int> writePosition_   = { 0 };
    std::vector<FloatType> maxValues_ = { 180, 0.0 };

    JUCE_LEAK_DETECTOR(StereoFieldBuffer) // NOLINT

    inline void computeDirection(std::vector<float>& directions, const FloatType left, const FloatType right) const
    {
        if (left == 0) {
            directions[45] = std::max(directions[45], std::abs(right));
        } else if (left * right > 0) {
        }
    }

    [[nodiscard]] inline auto computePosition(const juce::Rectangle<FloatType>& b, const FloatType left,
        const FloatType right) const -> juce::Point<FloatType>
    {
        return juce::Point<FloatType>(b.getCentreX() + FloatType(0.5) * b.getWidth() * (right - left),
            b.getCentreY() + FloatType(0.5) * b.getHeight() * (left + right));
    }

public:
    StereoFieldBuffer()  = default;
    ~StereoFieldBuffer() = default;

    StereoFieldBuffer(const StereoFieldBuffer& other) = delete;
    StereoFieldBuffer(StereoFieldBuffer&& other)      = delete;
    auto operator=(const StereoFieldBuffer& rhs) -> StereoFieldBuffer& = delete;
    auto operator=(StereoFieldBuffer&& rhs) -> StereoFieldBuffer& = delete;

    void setBufferSize(int newNumChannels, int newNumSamples)
    {
        sampleBuffer_.setSize(newNumChannels, newNumSamples);
        sampleBuffer_.clear();
        writePosition_ = 0;
    }

    void pushSampleBlock(juce::AudioBuffer<FloatType> buffer, int numSamples)
    {
        jassert(buffer.getNumChannels() == sampleBuffer_.getNumChannels());

        auto pos   = writePosition_.load();
        auto space = sampleBuffer_.getNumSamples() - pos;
        if (space >= numSamples) {
            for (int c = 0; c < sampleBuffer_.getNumChannels(); ++c) {
                sampleBuffer_.copyFrom(c, pos, buffer.getReadPointer(c), numSamples);
            }
            writePosition_ = pos + numSamples;
        } else {
            for (int c = 0; c < sampleBuffer_.getNumChannels(); ++c) {
                sampleBuffer_.copyFrom(c, pos, buffer.getReadPointer(c), space);
                sampleBuffer_.copyFrom(c, 0, buffer.getReadPointer(c, space), numSamples - space);
            }
            writePosition_ = numSamples - space;
        }
    }

    void resetMaxValues() { std::fill(maxValues_.begin(), maxValues_.end(), 0.0); }

    //  ==============================================================================

    [[nodiscard]] auto getOscilloscope(const int numSamples, const juce::Rectangle<FloatType> bounds, int leftIdx,
        int rightIdx) const -> juce::Path
    {
        juce::Path curve;
        auto pos = writePosition_.load();
        if (pos >= numSamples) {
            auto* left  = sampleBuffer_.getReadPointer(leftIdx, pos - numSamples);
            auto* right = sampleBuffer_.getReadPointer(rightIdx, pos - numSamples);
            curve.startNewSubPath(computePosition(bounds, *left, *right));
            ++left;
            ++right;
            for (int i = 1; i < numSamples; ++i) {
                curve.lineTo(computePosition(bounds, *left, *right));
                ++left;
                ++right;
            }
        } else {
            auto leftover = numSamples - pos;
            auto* left    = sampleBuffer_.getReadPointer(leftIdx, sampleBuffer_.getNumSamples() - leftover);
            auto* right   = sampleBuffer_.getReadPointer(rightIdx, sampleBuffer_.getNumSamples() - leftover);
            curve.startNewSubPath(computePosition(bounds, *left, *right));
            ++left;
            ++right;
            for (int i = 1; i < leftover; ++i) {
                curve.lineTo(computePosition(bounds, *left, *right));
                ++left;
                ++right;
            }
            left  = sampleBuffer_.getReadPointer(leftIdx);
            right = sampleBuffer_.getReadPointer(rightIdx);
            for (int i = 0; i < numSamples - leftover; ++i) {
                curve.lineTo(computePosition(bounds, *left, *right));
                ++left;
                ++right;
            }
        }

        return curve;
    }

    //  ==============================================================================

    void getDirections(std::vector<FloatType>& directions, int numSamples, int leftIdx, int rightIdx)
    {
        jassert(directions.size() == 180);
        std::fill(directions.begin(), directions.end(), 0.0);
        auto pos = writePosition_.load();

        if (pos >= numSamples) {
            auto* left  = sampleBuffer_.getReadPointer(leftIdx, pos - numSamples);
            auto* right = sampleBuffer_.getReadPointer(rightIdx, pos - numSamples);
            for (int i = 0; i < numSamples; ++i) {
                computeDirection(directions, *left, *right);
                ++left;
                ++right;
            }
        } else {
            auto leftover = numSamples - pos;
            auto* left    = sampleBuffer_.getReadPointer(leftIdx, sampleBuffer_.getNumSamples() - leftover);
            auto* right   = sampleBuffer_.getReadPointer(rightIdx, sampleBuffer_.getNumSamples() - leftover);
            for (int i = 0; i < leftover; ++i) {
                computeDirection(directions, *left, *right);
                ++left;
                ++right;
            }
            left  = sampleBuffer_.getReadPointer(leftIdx);
            right = sampleBuffer_.getReadPointer(rightIdx);
            for (int i = 0; i < numSamples - leftover; ++i) {
                computeDirection(directions, *left, *right);
                ++left;
                ++right;
            }
        }
    }
};
/*@}*/
} // namespace mc
