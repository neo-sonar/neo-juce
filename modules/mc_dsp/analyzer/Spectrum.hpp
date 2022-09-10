#ifndef MODERN_CIRCUITS_JUCE_MODULES_MC_DSP_SPECTRUM_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_MC_DSP_SPECTRUM_HPP

namespace mc {

/// \brief Component for the spectrum analyser.
struct Spectrum : juce::Component, juce::Timer {
    enum ColourIds {
        plot   = 0x1331600,
        grid   = 0x1331601,
        labels = 0x1331602,
    };

    struct LookAndFeelMethods {
        LookAndFeelMethods()          = default;
        virtual ~LookAndFeelMethods() = default;

        LookAndFeelMethods(const LookAndFeelMethods& other)                  = delete;
        LookAndFeelMethods(LookAndFeelMethods&& other)                       = delete;
        auto operator=(const LookAndFeelMethods& rhs) -> LookAndFeelMethods& = delete;
        auto operator=(LookAndFeelMethods&& rhs) -> LookAndFeelMethods&      = delete;

        virtual auto getAnalyserPathBounds(juce::Rectangle<int> const& area) -> juce::Rectangle<int>           = 0;
        virtual auto getAnalyserFrequencyLabelBounds(juce::Rectangle<int> const& area) -> juce::Rectangle<int> = 0;

        virtual auto drawAnalyzerGrid(juce::Graphics& g, juce::Rectangle<int> const& area) -> void   = 0;
        virtual auto drawAnalyzerLabels(juce::Graphics& g, juce::Rectangle<int> const& area) -> void = 0;
        virtual auto drawAnalyzerPath(juce::Graphics& g, juce::Rectangle<int> const& area, juce::Path const& path)
            -> void
            = 0;
    };

    explicit Spectrum(SpectrumSource& analyser);
    ~Spectrum() override = default;

    Spectrum(const Spectrum& other)                  = delete;
    Spectrum(Spectrum&& other)                       = delete;
    auto operator=(const Spectrum& rhs) -> Spectrum& = delete;
    auto operator=(Spectrum&& rhs) -> Spectrum&      = delete;

    auto paint(juce::Graphics& g) -> void override;
    auto resized() -> void override;

private:
    auto timerCallback() -> void override;

    SpectrumSource& processor_;
    juce::Rectangle<int> plotFrame_;
    juce::Rectangle<int> textFrame_;
    juce::Path path_;

    JUCE_LEAK_DETECTOR(Spectrum) // NOLINT
};

} // namespace mc
#endif // MODERN_CIRCUITS_JUCE_MODULES_MC_DSP_SPECTRUM_HPP
