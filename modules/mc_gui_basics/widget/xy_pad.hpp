#ifndef MODERN_CIRCUITS_PLUGINS_XY_PAD_HPP
#define MODERN_CIRCUITS_PLUGINS_XY_PAD_HPP

namespace mc
{
class XYPad : public juce::Component
{
public:
    XYPad();
    ~XYPad() override = default;

    auto paint(juce::Graphics& g) -> void override;
    auto resized() -> void override;

    [[nodiscard]] auto getXPosition() const noexcept -> float;
    [[nodiscard]] auto getYPosition() const noexcept -> float;
    [[nodiscard]] auto getNormalisedXPosition() const noexcept -> float;
    [[nodiscard]] auto getNormalisedYPosition() const noexcept -> float;
    auto setXPosition(float x) noexcept -> void;
    auto setYPosition(float y) noexcept -> void;
    auto setNormalisedXPosition(float x) noexcept -> void;
    auto setNormalisedYPosition(float y) noexcept -> void;
    [[nodiscard]] auto getXRange() const noexcept -> juce::NormalisableRange<float>;
    [[nodiscard]] auto getYRange() const noexcept -> juce::NormalisableRange<float>;
    auto setXRange(juce::NormalisableRange<float> const& newRange) noexcept -> void;
    auto setYRange(juce::NormalisableRange<float> const& newRange) noexcept -> void;

private:
    auto mouseMove(juce::MouseEvent const& event) -> void override;
    auto mouseDown(juce::MouseEvent const& event) -> void override;
    auto mouseDrag(juce::MouseEvent const& event) -> void override;

    [[nodiscard]] auto getValueFromPixel(int pixel, bool isXAxis) const -> float;
    [[nodiscard]] auto getPixelFromValue(float value, bool x) const -> int;
    [[nodiscard]] auto thumbHitTest(juce::MouseEvent const& event) const -> bool;

    juce::Point<float> position_;
    juce::NormalisableRange<float> xRange_;
    juce::NormalisableRange<float> yRange_;
    juce::Rectangle<int> thumb_ {0, 0, 8, 8};
    juce::Colour thumbColor_ = juce::Colours::grey;
    juce::Rectangle<int> bounds_ {};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(XYPad)  // NOLINT
};

}  // namespace mc

#endif  // MODERN_CIRCUITS_PLUGINS_XY_PAD_HPP
