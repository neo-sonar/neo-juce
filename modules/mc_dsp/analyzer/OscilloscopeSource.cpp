namespace mc {

auto OscilloscopeSource::process(juce::AudioBuffer<float> const& buffer) -> void { source_.process(buffer); }

auto OscilloscopeSource::process(juce::AudioBuffer<double> const& buffer) -> void { source_.process(buffer); }

auto OscilloscopeSource::currentScope() const noexcept -> span<float const> { return source_.buffer(); }

auto OscilloscopeSource::addChangeListener(juce::ChangeListener* l) -> void { source_.addChangeListener(l); }

auto OscilloscopeSource::removeChangeListener(juce::ChangeListener* l) -> void { source_.addChangeListener(l); }

} // namespace mc