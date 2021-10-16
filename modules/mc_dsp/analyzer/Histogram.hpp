#pragma once

namespace mc {

struct Histogram;

struct HistogramLookAndFeelMethods {
    virtual ~HistogramLookAndFeelMethods()                                            = default;
    virtual auto drawHistogram(juce::Graphics& g, Histogram const& histogram) -> void = 0;
};

struct Histogram : juce::Component, juce::Timer {
    using LookAndFeelMethods = HistogramLookAndFeelMethods;

    explicit Histogram(HistogramSource* source, juce::Range<float> range = juce::Range<float> { 0.0f, 1.3f });
    ~Histogram() override = default;

    MC_NODISCARD auto historyBuffer() const noexcept -> RingBuffer<float> const&;

    auto valueRange(juce::Range<float> const& range) noexcept -> void;
    MC_NODISCARD auto valueRange() const noexcept -> juce::Range<float> const&;

    auto historyToShow(Seconds<float> seconds) noexcept -> void;
    auto refreshRate(Hertz<int> rate) -> void;

    auto paint(juce::Graphics& g) -> void override;

private:
    auto timerCallback() -> void override;
    auto resizeBuffer() -> void;

    HistogramSource* source_ {};
    juce::Range<float> range_ { 1.0, 0.0 };
    RingBuffer<float> history_ {};
    Seconds<float> historyToKeep_ { 6.0f };
    Hertz<int> refreshRate_ { 30 };
};
} // namespace mc