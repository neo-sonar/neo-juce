namespace neo {
Spectrum::Spectrum(SpectrumSource& source) : _source { source }
{
    _source.addChangeListener(this);
    startTimerHz(30);
}

Spectrum::~Spectrum() { _source.removeChangeListener(this); }

auto Spectrum::paint(juce::Graphics& g) -> void
{
    if (auto* const lnf = dynamic_cast<LookAndFeelMethods*>(&getLookAndFeel()); lnf != nullptr) {
        juce::Graphics::ScopedSaveState const state(g);
        auto path = _source.makePath(getLocalBounds().toFloat());
        lnf->drawSpectrum(g, getLocalBounds(), path);
        return;
    }

    // You need to give a look&feel object to the constructor.
    jassertfalse;
}

auto Spectrum::timerCallback() -> void
{
    if (_newDataAvailable) {
        _newDataAvailable = false;
        repaint();
    }
}

auto Spectrum::changeListenerCallback(juce::ChangeBroadcaster* source) -> void
{
    jassertquiet(source == &_source);
    _newDataAvailable = true;
}
} // namespace neo
