namespace neo {

auto OscilloscopeSource::prepare(juce::dsp::ProcessSpec const& spec) -> void { _source.prepare(spec); }

auto OscilloscopeSource::process(juce::AudioBuffer<float> const& buffer) -> void { _source.process(buffer); }

auto OscilloscopeSource::reset() -> void { _source.reset(); }

auto OscilloscopeSource::currentScope() const noexcept -> std::span<float const> { return _source.buffer(); }

auto OscilloscopeSource::addChangeListener(juce::ChangeListener* l) -> void { _source.addChangeListener(l); }

auto OscilloscopeSource::removeChangeListener(juce::ChangeListener* l) -> void { _source.removeChangeListener(l); }

} // namespace neo
