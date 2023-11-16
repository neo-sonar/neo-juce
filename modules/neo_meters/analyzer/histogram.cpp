namespace neo {

Histogram::Histogram(HistogramSource* source, juce::Range<float> range) : _source { source }, _range { range }
{
    jassert(!range.isEmpty());
    startTimerHz(_refreshRate);
}

auto Histogram::historyBuffer() const noexcept -> RingBuffer<float> const& { return _history; }

auto Histogram::valueRange(juce::Range<float> const& range) noexcept -> void { _range = range; }

auto Histogram::valueRange() const noexcept -> juce::Range<float> const& { return _range; }

auto Histogram::historyToShow(Seconds<float> seconds) noexcept -> void
{
    _historyToKeep = seconds;
    resizeBuffer();
}

auto Histogram::refreshRate(int rate) -> void
{
    _refreshRate = rate;
    resizeBuffer();
    if (isTimerRunning()) { startTimerHz(_refreshRate); }
}

auto Histogram::paint(juce::Graphics& g) -> void
{
    auto* lnf = dynamic_cast<LookAndFeelMethods*>(&getLookAndFeel());
    if (lnf != nullptr) { lnf->drawHistogram(g, *this); }
}

auto Histogram::timerCallback() -> void
{
    _history.push(_source->popSample());
    repaint();
}

auto Histogram::resizeBuffer() -> void
{
    auto const size = static_cast<float>(_refreshRate) * _historyToKeep.count();
    _history.resize(static_cast<std::uint32_t>(size));
}
} // namespace neo
