#pragma once

namespace mc {

struct Histogram : juce::Component, juce::Timer {
    explicit Histogram(HistogramSource* source, juce::Range<float> range = juce::Range<float> { 0.0f, 1.3f });
    ~Histogram() override = default;

    auto paint(juce::Graphics& g) -> void override;
    auto resized() -> void override;

    auto setValueRange(juce::Range<float> const& range) noexcept -> void;
    auto setHistoryToShow(float seconds) noexcept -> void;
    auto setRefreshRate(int rateInHz) -> void;

private:
    auto timerCallback() -> void override;
    auto resizeBuffer() -> void;

    HistogramSource* source_ {};
    juce::Range<float> range_ { 1.0, 0.0 };
    RingBuffer<float> history_ {};
    float historyToKeepSeconds_ { 6.0f };
    int refreshRateHz_ { 30 };
};
} // namespace mc