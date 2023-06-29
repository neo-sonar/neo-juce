#pragma once

namespace mc {

struct WaveformSource {
    WaveformSource();
    ~WaveformSource();

    auto secondsToShow(Seconds<float> seconds) -> void;

    [[nodiscard]] auto levels(int channel) const -> std::span<juce::Range<float> const>;
    [[nodiscard]] auto numChannels() const -> int;

    void makeChannelPath(juce::Path& path, int channel) const;

    auto prepare(juce::dsp::ProcessSpec const& spec) -> void;

    template <typename ProcessContext>
    auto process(ProcessContext const& context) -> void;

    void reset();

private:
    struct ChannelInfo {
        ChannelInfo(WaveformSource& o, int blocks);

        void clear() noexcept;
        void pushSamples(float const* inputSamples, int num) noexcept;

        void pushSample(float newSample) noexcept;
        void numBlocksToShow(int newSize);

        WaveformSource& owner;
        juce::Array<juce::Range<float>> levels;
        juce::Range<float> value;
        std::atomic<int> nextSample { 0 };
        std::atomic<int> subSample { 0 };
    };

    void numBlocksToShow(int newNumSamples);
    void samplesPerBlock(int newSamplesPerPixel) noexcept;

    juce::OwnedArray<ChannelInfo> _channels;
    juce::dsp::ProcessSpec _spec { 44'100.0, 512, 2 };
    Seconds<float> _window { 3.0F };
    int _numSamples { 1024 };
    int _inputSamplesPerBlock { 256 };
};

template <typename ProcessContext>
auto WaveformSource::process(ProcessContext const& context) -> void
{
    auto inBlock  = context.getInputBlock();
    auto outBlock = context.getOutputBlock();
    if (ProcessContext::usesSeparateInputAndOutputBlocks()) { outBlock.copyFrom(inBlock); }

    for (auto i = 0; i < juce::jmin((int)outBlock.getNumChannels(), _channels.size()); ++i) {
        auto* ch = _channels.getUnchecked(i);
        ch->pushSamples(outBlock.getChannelPointer(i), (int)outBlock.getNumSamples());
    }
}

} // namespace mc
