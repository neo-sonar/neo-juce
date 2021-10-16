namespace mc {

Histogram::Histogram(HistogramSource* source, juce::Range<float> range) : source_ { source }, range_ { range }
{
    jassert(!range.isEmpty());
    startTimerHz(refreshRateHz_);
}

auto Histogram::historyBuffer() const noexcept -> RingBuffer<float> const& { return history_; }

auto Histogram::valueRange(juce::Range<float> const& range) noexcept -> void { range_ = range; }

auto Histogram::valueRange() const noexcept -> juce::Range<float> const& { return range_; }

auto Histogram::historyToShow(float seconds) noexcept -> void
{
    historyToKeepSeconds_ = seconds;
    resizeBuffer();
}

auto Histogram::refreshRate(int rateInHz) -> void
{
    refreshRateHz_ = rateInHz;
    resizeBuffer();
    if (isTimerRunning()) { startTimerHz(refreshRateHz_); }
}

auto Histogram::paint(juce::Graphics& g) -> void
{
    auto* lnf = dynamic_cast<LookAndFeelMethods*>(&getLookAndFeel());
    if (lnf != nullptr) { lnf->drawHistogram(g, *this); }
}

auto Histogram::timerCallback() -> void
{
    history_.push(source_->popSample());
    repaint();
}

auto Histogram::resizeBuffer() -> void
{
    history_.resize(static_cast<std::uint32_t>(static_cast<float>(refreshRateHz_) * historyToKeepSeconds_));
}
} // namespace mc