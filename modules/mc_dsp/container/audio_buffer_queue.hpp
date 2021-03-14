#ifndef MODERN_CIRCUITS_PLUGINS_AUDIO_BUFFER_QUEUE_HPP
#define MODERN_CIRCUITS_PLUGINS_AUDIO_BUFFER_QUEUE_HPP

namespace mc
{

template<typename SampleType>
class AudioBufferQueue
{
public:
    AudioBufferQueue() = default;

    static constexpr std::size_t order      = 9;
    static constexpr std::size_t bufferSize = 1U << order;
    static constexpr std::size_t numBuffers = 5;

    void push(SampleType const* dataToPush, std::size_t numSamples)
    {
        jassert(numSamples <= bufferSize);

        auto start1 = 0;
        auto size1  = 0;
        auto start2 = 0;
        auto size2  = 0;
        abstractFifo.prepareToWrite(1, start1, size1, start2, size2);

        jassert(size1 <= 1);
        jassert(size2 == 0);

        if (size1 > 0)
        {
            auto* const dest = buffers[static_cast<std::size_t>(start1)].data();
            auto const num   = static_cast<int>(juce::jmin(bufferSize, numSamples));
            juce::FloatVectorOperations::copy(dest, dataToPush, num);
        }

        abstractFifo.finishedWrite(size1);
    }

    void pop(SampleType* outputBuffer)
    {
        auto start1 = 0;
        auto size1  = 0;
        auto start2 = 0;
        auto size2  = 0;
        abstractFifo.prepareToRead(1, start1, size1, start2, size2);

        jassert(size1 <= 1);
        jassert(size2 == 0);

        if (size1 > 0)
        {
            auto const* const src = buffers[(std::size_t)start1].data();
            juce::FloatVectorOperations::copy(outputBuffer, src, static_cast<int>(bufferSize));
        }

        abstractFifo.finishedRead(size1);
    }

private:
    juce::AbstractFifo abstractFifo {numBuffers};
    std::array<std::array<SampleType, bufferSize>, numBuffers> buffers {};

    JUCE_DECLARE_NON_COPYABLE(AudioBufferQueue)  // NOLINT
};
}  // namespace mc
#endif  // MODERN_CIRCUITS_PLUGINS_AUDIO_BUFFER_QUEUE_HPP
