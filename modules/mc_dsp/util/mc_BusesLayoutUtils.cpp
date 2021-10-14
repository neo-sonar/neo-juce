namespace mc {
auto BusesLayoutUtils::isSameInOut(juce::AudioProcessor::BusesLayout const& layout) noexcept -> bool
{
    auto const inputSet  = layout.getMainInputChannelSet();
    auto const outputSet = layout.getMainOutputChannelSet();

    // main input & output must be active
    auto const disabled = juce::AudioChannelSet::disabled();
    if (inputSet == disabled || outputSet == disabled) { return false; }

    // main input & output must have the same channel count
    return inputSet == outputSet;
}

auto BusesLayoutUtils::isMonoInOut(juce::AudioProcessor::BusesLayout const& layout) noexcept -> bool
{
    return isSameInOut(layout) && (layout.getMainOutputChannelSet() == juce::AudioChannelSet::mono());
}

auto BusesLayoutUtils::isStereoInOut(juce::AudioProcessor::BusesLayout const& layout) noexcept -> bool
{
    return isSameInOut(layout) && (layout.getMainOutputChannelSet() == juce::AudioChannelSet::stereo());
}

} // namespace mc
