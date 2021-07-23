namespace mc {

auto TriggerClock::advance(std::int64_t numSamples) -> bool
{
    auto ticked { false };
    sampleCount_ += numSamples;
    for (std::int64_t i { 0 }; i < numSamples; ++i) {
        if (static_cast<std::uint64_t>(std::abs(sampleCount_) + i) % tickLength_ == 0) {
            return true;
        }
    }
    return false;
}

auto TriggerClock::reset(std::int64_t sampleCount) -> void { sampleCount_ = sampleCount; }

auto TriggerClock::setTickLength(Milliseconds milli) -> void
{
    tickLength_ = static_cast<std::uint64_t>(toSampleCount(milli, sampleRate_));
}

auto TriggerClock::setSampleRate(double sampleRate) -> void { sampleRate_ = sampleRate; }

}