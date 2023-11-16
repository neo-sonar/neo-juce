#pragma once

namespace neo {

struct Histogram;

struct HistogramLookAndFeelMethods {
    virtual ~HistogramLookAndFeelMethods()                                            = default;
    virtual auto drawHistogram(juce::Graphics& g, Histogram const& histogram) -> void = 0;
};

struct Histogram : juce::Component, juce::Timer {
    using LookAndFeelMethods = HistogramLookAndFeelMethods;

    explicit Histogram(HistogramSource* source, juce::Range<float> range = juce::Range<float> { 0.0F, 1.3F });
    ~Histogram() override = default;

    [[nodiscard]] auto historyBuffer() const noexcept -> RingBuffer<float> const&;

    auto valueRange(juce::Range<float> const& range) noexcept -> void;
    [[nodiscard]] auto valueRange() const noexcept -> juce::Range<float> const&;

    auto historyToShow(Seconds<float> seconds) noexcept -> void;
    auto refreshRate(int rate) -> void;

    auto paint(juce::Graphics& g) -> void override;

private:
    auto timerCallback() -> void override;
    auto resizeBuffer() -> void;

    HistogramSource* _source {};
    juce::Range<float> _range { 1.0, 0.0 };
    RingBuffer<float> _history {};
    Seconds<float> _historyToKeep { 6.0F };
    int _refreshRate { 30 };
};
} // namespace neo
