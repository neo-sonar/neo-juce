#pragma once

namespace mc {
LevelMeterSource::ChannelData::ChannelData(const size_t rmsWindow)
    : max(), maxOverall(), clip(false), reduction(1.0F), _hold(0), _rmsHistory((size_t)rmsWindow, 0.0), _rmsSum(0.0)

{
}

LevelMeterSource::ChannelData::ChannelData(ChannelData const& other)
    : max(other.max.load())
    , maxOverall(other.maxOverall.load())
    , clip(other.clip.load())
    , reduction(other.reduction.load())
    , _hold(other._hold.load())
    , _rmsHistory(8, 0.0)
    , _rmsSum(0.0)

{
}

auto LevelMeterSource::ChannelData::operator=(ChannelData const& other) -> ChannelData&
{
    max.store(other.max.load());
    maxOverall.store(other.maxOverall.load());
    clip.store(other.clip.load());
    reduction.store(other.reduction.load());
    _hold.store(other._hold.load());
    _rmsHistory.resize(other._rmsHistory.size(), 0.0);
    _rmsSum = 0.0;
    _rmsPtr = 0;
    return (*this);
}

auto LevelMeterSource::ChannelData::rmsAverage() const -> float
{
    if (!_rmsHistory.empty()) {
        auto const sum = std::accumulate(_rmsHistory.begin(), _rmsHistory.end(), 0.0);
        return static_cast<float>(std::sqrt(sum / static_cast<double>(_rmsHistory.size())));
    }

    return static_cast<float>(std::sqrt(_rmsSum));
}

auto LevelMeterSource::ChannelData::levels(juce::int64 time, float newMax, float newRms, juce::int64 newHoldMSecs)
    -> void
{
    if (newMax > 1.0 || newRms > 1.0) { clip = true; }

    maxOverall = fmaxf(maxOverall, newMax);
    if (newMax >= max) {
        max   = std::min(1.0F, newMax);
        _hold = time + newHoldMSecs;
    } else if (time > _hold) {
        max = std::min(1.0F, newMax);
    }
    pushRMS(std::min(1.0F, newRms));
}

auto LevelMeterSource::ChannelData::rmsSize(const size_t numBlocks) -> void
{
    _rmsHistory.assign(numBlocks, 0.0);
    _rmsSum = 0.0;
    if (numBlocks > 1) {
        _rmsPtr %= _rmsHistory.size();
    } else {
        _rmsPtr = 0;
    }
}

auto LevelMeterSource::ChannelData::pushRMS(float const newRMS) -> void
{
    double const squaredRMS = std::min(newRMS * newRMS, 1.0F);
    if (!_rmsHistory.empty()) {
        _rmsHistory[(size_t)_rmsPtr] = squaredRMS;
        _rmsPtr                      = (_rmsPtr + 1) % _rmsHistory.size();
    } else {
        _rmsSum = squaredRMS;
    }
}

LevelMeterSource::LevelMeterSource() : _lastMeasurement(0) { }

LevelMeterSource::~LevelMeterSource() { masterReference.clear(); }

auto LevelMeterSource::rmsWindow(Milliseconds<int> millis) -> void { _rmsWindow = millis; }

auto LevelMeterSource::prepare(juce::dsp::ProcessSpec const& spec) -> void
{
    auto const rmsWindowInSamples = _rmsWindow.count() * (float)spec.sampleRate / (float)spec.maximumBlockSize;
    _levels.resize(spec.numChannels, ChannelData(size_t(rmsWindowInSamples)));
    for (auto& l : _levels) { l.rmsSize(size_t(rmsWindowInSamples)); }
    _newDataFlag = true;
}

auto LevelMeterSource::reset() -> void
{
    clearAllClipFlags();
    clearAllMaxNums();
}

auto LevelMeterSource::decayIfNeeded() -> void
{
    juce::int64 const time = juce::Time::currentTimeMillis();
    if (time - _lastMeasurement < 100) { return; }

    _lastMeasurement = time;
    for (auto& level : _levels) {
        level.levels(_lastMeasurement, 0.0F, 0.0F, _holdMSecs);
        level.reduction = 1.0F;
    }

    _newDataFlag = true;
}

auto LevelMeterSource::reductionLevel(int channel, float const reduction) -> void
{
    if (not juce::isPositiveAndBelow(channel, static_cast<int>(_levels.size()))) { return; }
    _levels[size_t(channel)].reduction = reduction;
}

auto LevelMeterSource::setMaxHoldMS(const juce::int64 millis) -> void { _holdMSecs = millis; }

auto LevelMeterSource::reductionLevel(int channel) const -> float
{
    if (juce::isPositiveAndBelow(channel, static_cast<int>(_levels.size()))) {
        return _levels[size_t(channel)].reduction;
    }

    return -1.0F;
}

auto LevelMeterSource::maxLevel(int channel) const -> float { return _levels.at(size_t(channel)).max; }

auto LevelMeterSource::maxOverallLevel(int channel) const -> float { return _levels.at(size_t(channel)).maxOverall; }

auto LevelMeterSource::rmsLevel(int channel) const -> float { return _levels.at(size_t(channel)).rmsAverage(); }

auto LevelMeterSource::clipFlag(int channel) const -> bool { return _levels.at(size_t(channel)).clip; }

auto LevelMeterSource::clearClipFlag(int channel) -> void { _levels.at(size_t(channel)).clip = false; }

auto LevelMeterSource::clearAllClipFlags() -> void
{
    for (ChannelData& l : _levels) { l.clip = false; }
}

auto LevelMeterSource::clearMaxNum(int channel) -> void { _levels.at(size_t(channel)).maxOverall = infinity; }

auto LevelMeterSource::clearAllMaxNums() -> void
{
    for (ChannelData& l : _levels) { l.maxOverall = infinity; }
}

auto LevelMeterSource::numChannels() const -> int { return static_cast<int>(_levels.size()); }

auto LevelMeterSource::setSuspended(bool const shouldBeSuspended) -> void { _suspended = shouldBeSuspended; }

auto LevelMeterSource::checkNewDataFlag() const -> bool { return _newDataFlag; }

auto LevelMeterSource::resetNewDataFlag() -> void { _newDataFlag = false; }

} // end namespace mc
