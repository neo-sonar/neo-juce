namespace neo {

auto TriggerClock::advance(std::int64_t numSamples) -> bool
{
    auto const oldCount = _sampleCount;
    _sampleCount += numSamples;
    for (std::int64_t i { 0 }; i < numSamples; ++i) {
        if (static_cast<std::uint64_t>(std::abs(oldCount) + i) % _tickLength == 0) { return true; }
    }
    return false;
}

auto TriggerClock::reset(std::int64_t sampleCount) -> void { _sampleCount = sampleCount; }

auto TriggerClock::setTickLength(Milliseconds<double> milli) -> void
{
    _tickLength = static_cast<std::uint64_t>(toSampleCount(milli, _sampleRate));
}

auto TriggerClock::setSampleRate(double sampleRate) -> void { _sampleRate = sampleRate; }

} // namespace neo
