#pragma once

namespace mc {

/// This class implements a circular buffer to buffer audio samples.
/// At any time the GUI can ask for a stereo field visualisation of
/// two neightbouring channels.
template <typename FloatType>
struct StereoFieldBuffer {
private:
    juce::AudioBuffer<FloatType> _sampleBuffer;
    Atomic<int> _writePosition   = { 0 };
    Vector<FloatType> _maxValues = { 180, 0.0 };

    inline void computeDirection(Vector<float>& directions, const FloatType left, const FloatType right) const
    {
        if (left == 0) {
            directions[45] = std::max(directions[45], std::abs(right));
        } else if (left * right > 0) {
        }
    }

    [[nodiscard]] inline auto computePosition(juce::Rectangle<FloatType> const& b,
        const FloatType left,
        const FloatType right) const -> juce::Point<FloatType>
    {
        return juce::Point<FloatType>(b.getCentreX() + FloatType(0.5) * b.getWidth() * (right - left),
            b.getCentreY() + FloatType(0.5) * b.getHeight() * (left + right));
    }

public:
    StereoFieldBuffer()  = default;
    ~StereoFieldBuffer() = default;

    StereoFieldBuffer(StereoFieldBuffer const& other)                  = delete;
    StereoFieldBuffer(StereoFieldBuffer&& other)                       = delete;
    auto operator=(StereoFieldBuffer const& rhs) -> StereoFieldBuffer& = delete;
    auto operator=(StereoFieldBuffer&& rhs) -> StereoFieldBuffer&      = delete;

    void setBufferSize(int newNumChannels, int newNumSamples)
    {
        _sampleBuffer.setSize(newNumChannels, newNumSamples);
        _sampleBuffer.clear();
        _writePosition = 0;
    }

    void pushSampleBlock(juce::AudioBuffer<FloatType> buffer, int numSamples)
    {
        jassert(buffer.getNumChannels() == _sampleBuffer.getNumChannels());

        auto pos   = _writePosition.load();
        auto space = _sampleBuffer.getNumSamples() - pos;
        if (space >= numSamples) {
            for (int c = 0; c < _sampleBuffer.getNumChannels(); ++c) {
                _sampleBuffer.copyFrom(c, pos, buffer.getReadPointer(c), numSamples);
            }
            _writePosition = pos + numSamples;
        } else {
            for (int c = 0; c < _sampleBuffer.getNumChannels(); ++c) {
                _sampleBuffer.copyFrom(c, pos, buffer.getReadPointer(c), space);
                _sampleBuffer.copyFrom(c, 0, buffer.getReadPointer(c, space), numSamples - space);
            }
            _writePosition = numSamples - space;
        }
    }

    void resetMaxValues() { std::fill(_maxValues.begin(), _maxValues.end(), 0.0); }

    //  ==============================================================================

    [[nodiscard]] auto
    getOscilloscope(int const numSamples, const juce::Rectangle<FloatType> bounds, int leftIdx, int rightIdx) const
        -> juce::Path
    {
        juce::Path curve;
        auto pos = _writePosition.load();
        if (pos >= numSamples) {
            auto* left  = _sampleBuffer.getReadPointer(leftIdx, pos - numSamples);
            auto* right = _sampleBuffer.getReadPointer(rightIdx, pos - numSamples);
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
            auto* left    = _sampleBuffer.getReadPointer(leftIdx, _sampleBuffer.getNumSamples() - leftover);
            auto* right   = _sampleBuffer.getReadPointer(rightIdx, _sampleBuffer.getNumSamples() - leftover);
            curve.startNewSubPath(computePosition(bounds, *left, *right));
            ++left;
            ++right;
            for (int i = 1; i < leftover; ++i) {
                curve.lineTo(computePosition(bounds, *left, *right));
                ++left;
                ++right;
            }
            left  = _sampleBuffer.getReadPointer(leftIdx);
            right = _sampleBuffer.getReadPointer(rightIdx);
            for (int i = 0; i < numSamples - leftover; ++i) {
                curve.lineTo(computePosition(bounds, *left, *right));
                ++left;
                ++right;
            }
        }

        return curve;
    }

    //  ==============================================================================

    void getDirections(Vector<FloatType>& directions, int numSamples, int leftIdx, int rightIdx)
    {
        jassert(directions.size() == 180);
        ranges::fill(directions, 0.0);
        auto pos = _writePosition.load();

        if (pos >= numSamples) {
            auto* left  = _sampleBuffer.getReadPointer(leftIdx, pos - numSamples);
            auto* right = _sampleBuffer.getReadPointer(rightIdx, pos - numSamples);
            for (int i = 0; i < numSamples; ++i) {
                computeDirection(directions, *left, *right);
                ++left;
                ++right;
            }
        } else {
            auto leftover = numSamples - pos;
            auto* left    = _sampleBuffer.getReadPointer(leftIdx, _sampleBuffer.getNumSamples() - leftover);
            auto* right   = _sampleBuffer.getReadPointer(rightIdx, _sampleBuffer.getNumSamples() - leftover);
            for (int i = 0; i < leftover; ++i) {
                computeDirection(directions, *left, *right);
                ++left;
                ++right;
            }
            left  = _sampleBuffer.getReadPointer(leftIdx);
            right = _sampleBuffer.getReadPointer(rightIdx);
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
