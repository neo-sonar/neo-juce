#ifndef MODERN_CIRCUITS_PLUGINS_mc_BipolarFilter_HPP
#define MODERN_CIRCUITS_PLUGINS_mc_BipolarFilter_HPP

namespace mc {
struct BipolarFilter : juce::Component {
    enum ColourIds {
        backgroundColor = 0x1330001,
        lineColor       = 0x1330002,
        thumbColor      = 0x1330003,
    };

    struct Listener {
        virtual ~Listener() = default;

        virtual auto bipolarFilterValueChanged(BipolarFilter* bipolarFilter) -> void = 0;
        virtual auto bipolarFilterDragStarted(BipolarFilter* bipolarFilter) -> void  = 0;
        virtual auto bipolarFilterDragEnded(BipolarFilter* bipolarFilter) -> void    = 0;
    };

    /// \brief Creates a text box slider.
    /// \details When created, you can set up the text box slider's range with setRange(), etc.
    BipolarFilter() = default;

    /// \brief Creates a text box slider.
    /// \details When created, you can set up the text box slider's range with setRange(), etc.
    explicit BipolarFilter(juce::String const& componentName);

    /// \brief Destructor.
    ~BipolarFilter() noexcept override = default;

    auto setValue(double newValue) -> void;
    MC_NODISCARD auto getValue() const noexcept -> double;

    /// \brief Enables or disables the double-click to reset to default value feature.
    auto setDoubleClickReturnValue(bool shouldDoubleClickBeEnabled, double valueToSetOnDoubleClick) -> void;

    /// \brief Returns the values last set by setDoubleClickReturnValue() method.
    MC_NODISCARD auto getDoubleClickReturnValue() const noexcept -> double;

    /// \brief Returns true if double-clicking to reset to a default value is enabled.
    MC_NODISCARD auto isDoubleClickReturnEnabled() const noexcept -> bool;

    /// \brief Adds a listener to be called when this bipolar filter's value changes.
    auto addListener(Listener* listener) -> void;

    /// \brief Removes a previously-registered listener.
    auto removeListener(Listener* listener) -> void;

    auto paint(juce::Graphics& g) -> void override;
    auto resized() -> void override;

private:
    auto mouseDown(juce::MouseEvent const& mouseEvent) -> void override;
    auto mouseDrag(juce::MouseEvent const& mouseEvent) -> void override;
    auto mouseUp(juce::MouseEvent const& mouseEvent) -> void override;

    auto startDragging() -> void;
    auto stopDragging() -> void;

    juce::Range<double> range_ { -1.0, 1.0 };
    double currentValue_ { 0.0 };
    double defaultValue_ { 0.0 };
    bool doubleClickToResetIsEnabled_ { true };

    juce::Rectangle<float> thumbArea_ {};
    bool isDragging_ { false };

    juce::ListenerList<Listener> listeners_ {};

    JUCE_LEAK_DETECTOR(BipolarFilter) // NOLINT
};
} // namespace mc
#endif // MODERN_CIRCUITS_PLUGINS_mc_BipolarFilter_HPP
