namespace mc {

Oscilloscope::Oscilloscope(OscilloscopeSource& source) : _source { source } { _source.addChangeListener(this); }

Oscilloscope::~Oscilloscope() { _source.removeChangeListener(this); }

auto Oscilloscope::paint(juce::Graphics& g) -> void
{
    auto* const lnf = dynamic_cast<LookAndFeelMethods*>(&getLookAndFeel());
    if (lnf != nullptr) {
        auto const area = getLocalBounds();
        lnf->drawOscilloscopeBackground(g, area);
        lnf->drawOscilloscopePlot(g, area, _source, 1.5F, static_cast<float>(area.getHeight()) / 2.0F);
    }
}

auto Oscilloscope::changeListenerCallback(juce::ChangeBroadcaster* /*source*/) -> void { repaint(); }

} // namespace mc
