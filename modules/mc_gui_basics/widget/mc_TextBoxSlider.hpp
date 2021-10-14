#ifndef MODERN_CIRCUITS_PLUGINS_TEXT_BOX_SLIDER_HPP
#define MODERN_CIRCUITS_PLUGINS_TEXT_BOX_SLIDER_HPP

namespace mc {

/// \brief A text box slider control for changing a value via dragging or scrolling.
struct TextBoxSlider : juce::Component {
    /// \brief A class for receiving callbacks from a TextBoxSlider. To be told when a slider's value changes, you can
    /// register a TextBoxSlider::Listener object using TextBoxSlider::addListener().
    struct Listener {

        /// \brief Destructor.
        virtual ~Listener() = default;

        /// \brief Called when the text box slider's value is changed.
        /// \details This may be caused by dragging it, or by typing in its text entry box, or by a call to
        /// TextBoxSlider::setValue(). You can find out the new value using TextBoxSlider::getValue().
        virtual auto textBoxSliderValueChanged(TextBoxSlider* slider) -> void = 0;

        /// \brief Called when the text box slider is about to be dragged.
        /// \details This is called when a drag begins, then it's followed by multiple calls to sliderValueChanged(),
        /// and then sliderDragEnded() is called after the user lets go.
        virtual auto textBoxSliderDragStarted(TextBoxSlider* slider) -> void = 0;

        /// \brief Called after a drag operation has finished.
        virtual auto textBoxSliderDragEnded(TextBoxSlider* slider) -> void = 0;
    };

    /// \brief Creates a text box slider.
    /// \details When created, you can set up the text box slider's range with setRange(), etc.
    TextBoxSlider();

    /// \brief Creates a text box slider.
    /// \details When created, you can set up the text box slider's range with setRange(), etc.
    explicit TextBoxSlider(juce::String const& componentName);

    /// \brief Destructor.
    ~TextBoxSlider() noexcept override = default;

    /// \brief Changes the slider's current value.
    auto setValue(double newValue, juce::NotificationType notification = juce::sendNotificationAsync) -> void;

    /// \brief Returns the slider's current value.
    MC_NODISCARD auto getValue() const noexcept -> double;

    /// \brief Sets the limits that the text box slider's value can take.
    auto setRange(juce::Range<double> newRange, double newInterval) -> void;

    /// \brief Returns the text box slider's range.
    MC_NODISCARD auto getRange() const noexcept -> juce::Range<double>;

    /// \brief Returns the current maximum value.
    MC_NODISCARD auto getMaximum() const noexcept -> double;

    /// \brief Returns the current minimum value.
    MC_NODISCARD auto getMinimum() const noexcept -> double;

    /// \brief Returns the current step-size for value.
    MC_NODISCARD auto getInterval() const noexcept -> double;

    /// \brief Enables or disables the double-click to reset to default value feature.
    auto setDoubleClickReturnValue(bool shouldDoubleClickBeEnabled, double valueToSetOnDoubleClick) -> void;

    /// \brief Returns the values last set by setDoubleClickReturnValue() method.
    MC_NODISCARD auto getDoubleClickReturnValue() const noexcept -> double;

    /// \brief Returns true if double-clicking to reset to a default value is enabled.
    MC_NODISCARD auto isDoubleClickReturnEnabled() const noexcept -> bool;

    /// \brief Makes the text-box editable.
    auto setTextBoxIsEditable(bool shouldBeEditable) -> void;

    /// \brief Returns true if the text-box is read-only.
    MC_NODISCARD auto isTextBoxEditable() const noexcept -> bool;

    /// \brief You can assign a lambda to this callback object to have it called when the slider value is changed.
    std::function<void()> onValueChange {};

    /// \brief You can assign a lambda to this callback object to have it called when the slider's drag begins.
    std::function<void()> onDragStart {};

    /// \brief You can assign a lambda to this callback object to have it called when the slider's drag ends.
    std::function<void()> onDragEnd {};

    /// \brief You can assign a lambda that will be used to convert textual values to the slider's normalised position.
    std::function<double(juce::String const&)> valueFromText {};

    /// \brief You can assign a lambda that will be used to convert the slider's normalised position to a textual value.
    std::function<juce::String(double)> textFromValue {};

    /// \brief Convert string representation to value.
    MC_NODISCARD auto getValueFromText(juce::String const& text) const -> double;

    /// \brief Convert value to string representation.
    MC_NODISCARD auto getTextFromValue(double value) const -> juce::String;

    /// \brief Sets the style of justification to be used for positioning the text.
    auto setJustificationType(juce::Justification justification) -> void;

    /// \brief Returns the type of justification, as set in setJustificationType().
    MC_NODISCARD auto getJustificationType() const noexcept -> juce::Justification;

    /// \brief Adds a listener to be called when this text box slider's value changes.
    auto addListener(Listener* listener) -> void;

    /// \brief Removes a previously-registered listener.
    auto removeListener(Listener* listener) -> void;

    /// \brief Overrides juce::Component.
    auto resized() -> void override;

private:
    auto mouseDrag(juce::MouseEvent const& event) -> void override;
    auto mouseUp(juce::MouseEvent const& event) -> void override;
    auto mouseDoubleClick(juce::MouseEvent const& event) -> void override;
    auto mouseWheelMove(juce::MouseEvent const& event, juce::MouseWheelDetails const& wheel) -> void override;

    auto startDrag() -> void;
    auto stopDrag() -> void;

    juce::Range<double> range_ { 0.0, 10.0 };
    double value_ { 1.0 };
    double interval_ { 0.1 };
    double defaultValue_ { 1.0 };

    juce::Label text_;
    bool isDragging_ { false };
    bool doubleClickToResetIsEnabled_ { true };

    juce::ListenerList<Listener> listenerList_ {};

    JUCE_LEAK_DETECTOR(TextBoxSlider) // NOLINT
};

/// \brief A text box slider control for changing a value via dragging or scrolling.
struct TextBoxSliderV2 : juce::Slider {
    /// \brief Creates a text box slider.
    /// \details When created, you can set up the text box slider's range with setRange(), etc.
    TextBoxSliderV2();

    /// \brief Destructor.
    ~TextBoxSliderV2() noexcept override = default;

private:
    JUCE_LEAK_DETECTOR(TextBoxSliderV2) // NOLINT
};

} // namespace mc

#endif // MODERN_CIRCUITS_PLUGINS_TEXT_BOX_SLIDER_HPP
