namespace mc {
Spectrum::Spectrum(SpectrumSource& analyser)
    : processor_ { analyser } { startTimerHz(30); }

auto Spectrum::paint(juce::Graphics& g) -> void
{
    if (auto* const lnf = dynamic_cast<LookAndFeelMethods*>(&getLookAndFeel()); lnf != nullptr) {
        juce::Graphics::ScopedSaveState state(g);
        lnf->drawAnalyzerLabels(g, textFrame_);
        lnf->drawAnalyzerGrid(g, plotFrame_);
        lnf->drawAnalyzerPath(g, plotFrame_, path_);
        return;
    }

    // You need to give a look&feel object to the constructor.
    jassertfalse;
}

auto Spectrum::resized() -> void
{
    if (auto* const lnf = dynamic_cast<LookAndFeelMethods*>(&getLookAndFeel()); lnf != nullptr) {
        auto area  = getLocalBounds().reduced(3);
        plotFrame_ = lnf->getAnalyserPathBounds(area);
        textFrame_ = lnf->getAnalyserFrequencyLabelBounds(area);
    }
}

auto Spectrum::timerCallback() -> void
{
    if (processor_.checkForNewData()) {
        processor_.createPath(path_, plotFrame_.toFloat(), 10.0f);
        repaint();
    }
}
} // namespace mc