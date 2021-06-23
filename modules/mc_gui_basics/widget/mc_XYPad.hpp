#ifndef MODERN_CIRCUITS_PLUGINS_XY_PAD_HPP
#define MODERN_CIRCUITS_PLUGINS_XY_PAD_HPP

namespace mc
{
struct XYPad : juce::Component
{
    struct Listener
    {
        virtual ~Listener() = default;

        virtual auto xypadChanged(XYPad* pad, juce::Point<float> position) -> void = 0;
        virtual auto xypadDragStarted(XYPad* pad) -> void                          = 0;
        virtual auto xypadDragEnded(XYPad* pad) -> void                            = 0;
    };

    struct LookAndFeelMethods
    {
        virtual ~LookAndFeelMethods() = default;

        virtual auto drawXYPad(juce::Graphics& g, juce::Rectangle<float> thumbBounds, XYPad& pad) -> void = 0;
        virtual auto getXYPadThumbDiameter(XYPad& pad) -> int                                             = 0;
    };

    XYPad();
    ~XYPad() override = default;

    [[nodiscard]] auto getValueX() const noexcept -> float;
    [[nodiscard]] auto getValueY() const noexcept -> float;
    auto setValueX(float x) -> void;
    auto setValueY(float y) -> void;

    [[nodiscard]] auto getNormalizedX() const noexcept -> float;
    [[nodiscard]] auto getNormalizedY() const noexcept -> float;
    auto setNormalizedX(float x) -> void;
    auto setNormalizedY(float y) -> void;

    [[nodiscard]] auto getXRange() const noexcept -> juce::NormalisableRange<float>;
    [[nodiscard]] auto getYRange() const noexcept -> juce::NormalisableRange<float>;
    auto setXRange(juce::NormalisableRange<float> const& newRange) -> void;
    auto setYRange(juce::NormalisableRange<float> const& newRange) -> void;

    [[nodiscard]] auto getDirectionX() const noexcept -> bool;
    [[nodiscard]] auto getDirectionY() const noexcept -> bool;
    auto setDirectionX(bool startShouldBeOnLeft) -> void;
    auto setDirectionY(bool startShouldBeOnTop) -> void;

    [[nodiscard]] auto isOverThumb() const noexcept -> bool;
    [[nodiscard]] auto isDragging() const noexcept -> bool;

    auto addListener(Listener* listener) -> void { listeners_.add(listener); }
    auto removeListener(Listener* listener) -> void { listeners_.remove(listener); }

private:
    auto paint(juce::Graphics& g) -> void override;
    auto resized() -> void override;

    auto mouseMove(juce::MouseEvent const& event) -> void override;
    auto mouseDown(juce::MouseEvent const& event) -> void override;
    auto mouseUp(juce::MouseEvent const& event) -> void override;
    auto mouseDrag(juce::MouseEvent const& event) -> void override;

    [[nodiscard]] auto getValueFromPixel(int pixel, bool isXAxis) const -> float;
    [[nodiscard]] auto getPixelFromNormalizedValue(float value, bool x) const -> int;
    [[nodiscard]] auto thumbHitTest(juce::MouseEvent const& event) const -> bool;

    auto updatePosition() -> void;

    auto startDragging() -> void;
    auto stopDragging() -> void;

    juce::Point<float> normalizedValues_ {};
    juce::NormalisableRange<float> xRange_ {};
    juce::NormalisableRange<float> yRange_ {};
    bool startShouldBeOnLeft_ {true};
    bool startShouldBeOnTop_ {true};

    juce::Rectangle<int> thumb_ {0, 0, 8, 8};
    juce::Colour thumbColor_ {juce::Colours::grey};
    juce::Rectangle<int> bounds_ {};
    bool isDragging_ {false};
    bool isOverThumb_ {false};

    juce::ListenerList<Listener> listeners_ {};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(XYPad)  // NOLINT
};

}  // namespace mc

#endif  // MODERN_CIRCUITS_PLUGINS_XY_PAD_HPP
