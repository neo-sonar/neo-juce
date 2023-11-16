#pragma once

namespace neo {

struct Waveform;

struct WaveformLookAndFeelMethods {
    virtual ~WaveformLookAndFeelMethods() = default;
    virtual auto drawWaveform(juce::Graphics& g, juce::Rectangle<int> area, Waveform const& wave, int ch) -> void = 0;
};

struct WaveformColorIDs {
    inline static constexpr auto background = 0x1331800;
    inline static constexpr auto waveform   = 0x1331801;
};

struct Waveform final : juce::Component, juce::Timer {
    using LookAndFeelMethods = WaveformLookAndFeelMethods;
    using ColorIDs           = WaveformColorIDs;

    explicit Waveform(WaveformSource& source);
    ~Waveform() override = default;

    auto source() -> WaveformSource&;
    [[nodiscard]] auto source() const -> WaveformSource const&;

    auto refreshRate(int frequencyInHz) -> void;

private:
    auto paint(juce::Graphics& /*g*/) -> void override;
    auto timerCallback() -> void override;

    WaveformSource& _source;
};

} // namespace neo
