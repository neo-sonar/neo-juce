namespace mc {

WaveformSource::ChannelInfo::ChannelInfo(WaveformSource& o, int blocks) : owner(o)
{
    numBlocksToShow(blocks);
    clear();
}

void WaveformSource::ChannelInfo::clear() noexcept
{
    levels.fill({});
    value     = {};
    subSample = 0;
}

void WaveformSource::ChannelInfo::pushSamples(float const* inputSamples, int num) noexcept
{
    for (auto i = 0; i < num; ++i) { pushSample(inputSamples[i]); }
}

void WaveformSource::ChannelInfo::pushSample(float newSample) noexcept
{
    if (--subSample <= 0) {
        if (++nextSample == levels.size()) { nextSample = 0; }
        levels.getReference(nextSample) = value;
        subSample                       = owner._inputSamplesPerBlock;
        value                           = juce::Range<float>(newSample, newSample);
    } else {
        value = value.getUnionWith(newSample);
    }
}

void WaveformSource::ChannelInfo::numBlocksToShow(int newSize)
{
    levels.removeRange(newSize, levels.size());
    levels.insertMultiple(-1, {}, newSize - levels.size());
    if (nextSample >= newSize) { nextSample = 0; }
}

WaveformSource::WaveformSource() = default;

WaveformSource::~WaveformSource() = default;

auto WaveformSource::secondsToShow(Seconds<float> seconds) -> void
{
    _window                    = seconds;
    auto const blocksPerSecond = (float)_spec.sampleRate / (float)_inputSamplesPerBlock;
    samplesPerBlock(_inputSamplesPerBlock);
    numBlocksToShow(juce::roundToInt(blocksPerSecond * _window.count()));
}

void WaveformSource::reset()
{
    for (auto* c : _channels) { c->clear(); }
}

auto WaveformSource::prepare(juce::dsp::ProcessSpec const& spec) -> void
{
    _spec = spec;
    _channels.clear();
    for (auto i { 0U }; i < spec.numChannels; ++i) { _channels.add(std::make_unique<ChannelInfo>(*this, _numSamples)); }
    secondsToShow(_window);
}

auto WaveformSource::levels(int channel) const -> Span<juce::Range<float> const>
{
    return { _channels[channel]->levels.begin(), static_cast<std::size_t>(_channels[channel]->levels.size()) };
}

auto WaveformSource::numChannels() const -> int { return _channels.size(); }

void WaveformSource::makeChannelPath(juce::Path& path, int channel) const
{
    auto const l          = levels(channel);
    auto const numLevels  = static_cast<int>(l.size());
    auto const nextSample = _channels[channel]->nextSample.load();

    path.preallocateSpace(4 * numLevels + 8);
    path.startNewSubPath(0.0F, -(l[static_cast<size_t>((nextSample) % numLevels)].getEnd()));

    for (auto i = 1; i < numLevels; ++i) {
        auto const level = -(l[static_cast<size_t>((nextSample + i) % numLevels)].getEnd());
        path.lineTo((float)i, level);
    }

    for (auto i = numLevels; --i >= 0;) {
        path.lineTo((float)i, -(l[static_cast<size_t>((nextSample + i) % numLevels)].getStart()));
    }

    path.closeSubPath();
}

void WaveformSource::samplesPerBlock(int newSamplesPerPixel) noexcept { _inputSamplesPerBlock = newSamplesPerPixel; }

void WaveformSource::numBlocksToShow(int newNumSamples)
{
    _numSamples = newNumSamples;
    for (auto* c : _channels) { c->numBlocksToShow(newNumSamples); }
}

} // namespace mc
