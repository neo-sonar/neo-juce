#pragma once

namespace neo {

struct Spectrum;

struct SpectrumLookAndFeelMethods {
    SpectrumLookAndFeelMethods()          = default;
    virtual ~SpectrumLookAndFeelMethods() = default;

    virtual auto drawSpectrum(juce::Graphics& g, juce::Rectangle<int> area, juce::Path const& path) -> void = 0;
};

struct SpectrumColorIDs {
    inline static constexpr auto plot   = 0x1331600;
    inline static constexpr auto grid   = 0x1331601;
    inline static constexpr auto labels = 0x1331602;
};

/// \brief Component for the spectrum analyser.
struct Spectrum final : juce::Component, juce::ChangeListener, juce::Timer {
    using ColorIDs           = SpectrumColorIDs;
    using LookAndFeelMethods = SpectrumLookAndFeelMethods;

    explicit Spectrum(SpectrumSource& source);
    ~Spectrum() override;

    auto paint(juce::Graphics& g) -> void override;

private:
    auto timerCallback() -> void override;
    auto changeListenerCallback(juce::ChangeBroadcaster* source) -> void override;

    SpectrumSource& _source;
    bool _newDataAvailable { false };

    JUCE_LEAK_DETECTOR(Spectrum) // NOLINT
};

} // namespace neo
