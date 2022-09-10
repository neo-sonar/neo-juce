namespace mc {

auto OscilloscopeSource::process(juce::AudioBuffer<float> const& buffer) -> void { _source.process(buffer); }

auto OscilloscopeSource::process(juce::AudioBuffer<double> const& buffer) -> void { _source.process(buffer); }

auto OscilloscopeSource::currentScope() const noexcept -> Span<float const> { return _source.buffer(); }

auto OscilloscopeSource::addChangeListener(juce::ChangeListener* l) -> void { _source.addChangeListener(l); }

auto OscilloscopeSource::removeChangeListener(juce::ChangeListener* l) -> void { _source.removeChangeListener(l); }

} // namespace mc
