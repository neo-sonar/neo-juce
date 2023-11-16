namespace neo {

Waveform::Waveform(WaveformSource& source) : _source { source } { refreshRate(30); }

void Waveform::refreshRate(int frequencyInHz) { startTimerHz(frequencyInHz); }

auto Waveform::source() -> WaveformSource& { return _source; }
auto Waveform::source() const -> WaveformSource const& { return _source; }

void Waveform::timerCallback() { repaint(); }

void Waveform::paint(juce::Graphics& g)
{
    auto* const lnf = dynamic_cast<LookAndFeelMethods*>(&getLookAndFeel());
    if (lnf == nullptr) { return; }

    auto bounds              = getLocalBounds().toFloat();
    auto const numChannels   = source().numChannels();
    auto const channelHeight = bounds.getHeight() / static_cast<float>(std::max(1, numChannels));

    for (auto ch { 0 }; ch < numChannels; ++ch) {
        auto const channelBounds = bounds.removeFromTop(channelHeight).toNearestInt();
        g.reduceClipRegion(channelBounds);
        lnf->drawWaveform(g, channelBounds, *this, ch);
    }
}

} // namespace neo
