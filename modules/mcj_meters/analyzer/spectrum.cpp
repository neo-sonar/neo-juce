namespace mc {
Spectrum::Spectrum(SpectrumSource& source) : _source { source } { _source.addChangeListener(this); }

Spectrum::~Spectrum() { _source.removeChangeListener(this); }

auto Spectrum::paint(juce::Graphics& g) -> void
{
    auto* const lnf = dynamic_cast<LookAndFeelMethods*>(&getLookAndFeel());
    if (lnf != nullptr) {
        juce::Graphics::ScopedSaveState const state(g);
        lnf->drawAnalyzerLabels(g, _textFrame);
        lnf->drawAnalyzerGrid(g, _plotFrame);
        lnf->drawAnalyzerPath(g, _plotFrame, _path);
        return;
    }

    // You need to give a look&feel object to the constructor.
    jassertfalse;
}

auto Spectrum::resized() -> void
{
    auto* const lnf = dynamic_cast<LookAndFeelMethods*>(&getLookAndFeel());
    if (lnf != nullptr) {
        auto area  = getLocalBounds().reduced(3);
        _plotFrame = lnf->getAnalyserPathBounds(area);
        _textFrame = lnf->getAnalyserFrequencyLabelBounds(area);
    }
}

auto Spectrum::changeListenerCallback(juce::ChangeBroadcaster* source) -> void
{
    jassertquiet(source == &_source);
    _path = _source.makePath(_plotFrame.toFloat());
    repaint();
}
} // namespace mc
