namespace mc {

Histogram::Histogram(HistogramSource* source, juce::Range<float> range) : source_ { source }, range_ { range }
{
    jassert(!range.isEmpty());
    startTimerHz(refreshRateHz_);
}

auto Histogram::paint(juce::Graphics& g) -> void
{
    if (!history_.empty()) {
        // intentionally swapped
        auto const start = range_.getEnd();
        auto const end   = range_.getStart();

        auto path = juce::Path {};
        path.preallocateSpace(static_cast<int>(history_.size()));
        path.startNewSubPath(0.0f, juce::jmap(history_[0], start, end, 0.0f, static_cast<float>(getHeight())));

        for (std::uint32_t i = 1; i < history_.size(); ++i) {
            auto const x = juce::jmap(static_cast<int>(i), 0, static_cast<int>(history_.size() - 1), 0, getWidth());
            auto const y = juce::jmap(history_[i], start, end, 0.0f, static_cast<float>(getHeight()));
            path.lineTo(static_cast<float>(x), y);
        }

        // findColour(BundleColors::primaryLedHighlight, true).withAlpha(0.95f)
        g.setColour(juce::Colours::red);
        g.strokePath(path, juce::PathStrokeType { 1.5f });
    }
}

auto Histogram::resized() -> void { }

auto Histogram::setValueRange(juce::Range<float> const& range) noexcept -> void { range_ = range; }

auto Histogram::setHistoryToShow(float seconds) noexcept -> void
{
    historyToKeepSeconds_ = seconds;
    resizeBuffer();
}

auto Histogram::setRefreshRate(int rateInHz) -> void
{
    refreshRateHz_ = rateInHz;
    resizeBuffer();
    if (isTimerRunning()) { startTimerHz(refreshRateHz_); }
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