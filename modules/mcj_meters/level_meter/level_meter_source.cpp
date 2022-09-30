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

auto LevelMeterSource::ChannelData::getAvgRMS() const -> float
{
    if (!_rmsHistory.empty()) {
        auto const sum = std::accumulate(_rmsHistory.begin(), _rmsHistory.end(), 0.0);
        return static_cast<float>(std::sqrt(sum / static_cast<double>(_rmsHistory.size())));
    }

    return static_cast<float>(std::sqrt(_rmsSum));
}

void LevelMeterSource::ChannelData::setLevels(const juce::int64 time,
    float const newMax,
    float const newRms,
    const juce::int64 newHoldMSecs)
{
    if (newMax > 1.0 || newRms > 1.0) { clip = true; }

    maxOverall = fmaxf(maxOverall, newMax);
    if (newMax >= max) {
        max   = std::min(1.0F, newMax);
        _hold = time + newHoldMSecs;
    } else if (time > _hold) {
        max = std::min(1.0F, newMax);
    }
    pushNextRMS(std::min(1.0F, newRms));
}

void LevelMeterSource::ChannelData::setRMSsize(const size_t numBlocks)
{
    _rmsHistory.assign(numBlocks, 0.0);
    _rmsSum = 0.0;
    if (numBlocks > 1) {
        _rmsPtr %= _rmsHistory.size();
    } else {
        _rmsPtr = 0;
    }
}

void LevelMeterSource::ChannelData::pushNextRMS(float const newRMS)
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

void LevelMeterSource::resize(int const channels, int const rmsWindow)
{
    _levels.resize(size_t(channels), ChannelData(size_t(rmsWindow)));
    for (ChannelData& l : _levels) { l.setRMSsize(size_t(rmsWindow)); }

    _newDataFlag = true;
}

void LevelMeterSource::decayIfNeeded()
{
    juce::int64 const time = juce::Time::currentTimeMillis();
    if (time - _lastMeasurement < 100) { return; }

    _lastMeasurement = time;
    for (auto& level : _levels) {
        level.setLevels(_lastMeasurement, 0.0F, 0.0F, _holdMSecs);
        level.reduction = 1.0F;
    }

    _newDataFlag = true;
}

void LevelMeterSource::setReductionLevel(int const channel, float const reduction)
{
    if (juce::isPositiveAndBelow(channel, static_cast<int>(_levels.size()))) {
        _levels[size_t(channel)].reduction = reduction;
    }
}

void LevelMeterSource::setReductionLevel(float const reduction)
{
    for (auto& channel : _levels) { channel.reduction = reduction; }
}

void LevelMeterSource::setMaxHoldMS(const juce::int64 millis) { _holdMSecs = millis; }

auto LevelMeterSource::getReductionLevel(int const channel) const -> float
{
    if (juce::isPositiveAndBelow(channel, static_cast<int>(_levels.size()))) {
        return _levels[size_t(channel)].reduction;
    }

    return -1.0F;
}

auto LevelMeterSource::getMaxLevel(int const channel) const -> float { return _levels.at(size_t(channel)).max; }

auto LevelMeterSource::getMaxOverallLevel(int const channel) const -> float
{
    return _levels.at(size_t(channel)).maxOverall;
}

auto LevelMeterSource::getRMSLevel(int const channel) const -> float { return _levels.at(size_t(channel)).getAvgRMS(); }

auto LevelMeterSource::getClipFlag(int const channel) const -> bool { return _levels.at(size_t(channel)).clip; }

void LevelMeterSource::clearClipFlag(int const channel) { _levels.at(size_t(channel)).clip = false; }

void LevelMeterSource::clearAllClipFlags()
{
    for (ChannelData& l : _levels) { l.clip = false; }
}

void LevelMeterSource::clearMaxNum(int const channel) { _levels.at(size_t(channel)).maxOverall = infinity; }

void LevelMeterSource::clearAllMaxNums()
{
    for (ChannelData& l : _levels) { l.maxOverall = infinity; }
}

auto LevelMeterSource::getNumChannels() const -> int { return static_cast<int>(_levels.size()); }

void LevelMeterSource::setSuspended(bool const shouldBeSuspended) { _suspended = shouldBeSuspended; }

auto LevelMeterSource::checkNewDataFlag() const -> bool { return _newDataFlag; }

void LevelMeterSource::resetNewDataFlag() { _newDataFlag = false; }

} // end namespace mc
