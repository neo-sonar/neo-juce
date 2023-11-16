#pragma once

namespace neo {
struct XYPad : juce::Component {
    enum ColourIds {
        backgroundColor  = 0x1330101,
        outlineColor     = 0x1330102,
        thumbNormalColor = 0x1330103,
        thumbOverColor   = 0x1330104,
        thumbDownColor   = 0x1330105,
    };

    struct Listener {
        virtual ~Listener() = default;

        virtual auto xypadChanged(XYPad* pad, juce::Point<float> position) -> void = 0;
        virtual auto xypadDragStarted(XYPad* pad) -> void                          = 0;
        virtual auto xypadDragEnded(XYPad* pad) -> void                            = 0;
    };

    struct LookAndFeelMethods {
        virtual ~LookAndFeelMethods() = default;

        virtual auto drawXYPad(juce::Graphics& g, juce::Rectangle<float> thumbBounds, XYPad& pad) -> void = 0;
        virtual auto getXYPadThumbDiameter(XYPad& pad) -> int                                             = 0;
    };

    explicit XYPad(juce::String const& name = {});
    ~XYPad() override = default;

    [[nodiscard]] auto getValueX() const -> float;
    [[nodiscard]] auto getValueY() const -> float;
    auto setValueX(float x) -> void;
    auto setValueY(float y) -> void;

    [[nodiscard]] auto getNormalizedX() const -> float;
    [[nodiscard]] auto getNormalizedY() const -> float;
    auto setNormalizedX(float x) -> void;
    auto setNormalizedY(float y) -> void;

    [[nodiscard]] auto getXRange() const -> juce::NormalisableRange<float>;
    [[nodiscard]] auto getYRange() const -> juce::NormalisableRange<float>;
    auto setXRange(juce::NormalisableRange<float> const& newRange) -> void;
    auto setYRange(juce::NormalisableRange<float> const& newRange) -> void;

    [[nodiscard]] auto getDirectionX() const -> bool;
    [[nodiscard]] auto getDirectionY() const -> bool;
    auto setDirectionX(bool startShouldBeOnLeft) -> void;
    auto setDirectionY(bool startShouldBeOnTop) -> void;

    [[nodiscard]] auto isOverThumb() const -> bool;
    [[nodiscard]] auto isDragging() const -> bool;

    auto addListener(Listener* listener) -> void { _listeners.add(listener); }
    auto removeListener(Listener* listener) -> void { _listeners.remove(listener); }

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

    juce::Point<float> _normalizedValues {};
    juce::NormalisableRange<float> _xRange {};
    juce::NormalisableRange<float> _yRange {};
    bool _startShouldBeOnLeft { true };
    bool _startShouldBeOnTop { true };

    juce::Rectangle<int> _thumb { 0, 0, 8, 8 };
    juce::Colour _thumbColor { juce::Colours::grey };
    juce::Rectangle<int> _bounds {};
    bool _isDragging { false };
    bool _isOverThumb { false };

    juce::ListenerList<Listener> _listeners {};

    JUCE_LEAK_DETECTOR(XYPad) // NOLINT
};

} // namespace neo
