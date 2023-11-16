#pragma once

namespace neo {

/// \brief An object of this class maintains a connection between a
/// XYPad and a plug-in parameter of type choice.
///
/// \details During the lifetime of this object it keeps the two things in sync,
/// making it easy to connect a selector to a parameter. When this object is deleted,
/// the connection is broken. Make sure that your parameter and Selector are not
/// deleted before this object!
struct XYPadAttachment final : XYPad::Listener {
    /// \brief Creates a connection between a plug-in parameter and a Slider.
    ///
    /// \param parameterX    The parameter to use for the x-axis
    /// \param parameterY    The parameter to use for the y-axis
    /// \param pad           The XYPad to use
    /// \param undoManager   An optional juce::UndoManager
    XYPadAttachment(juce::RangedAudioParameter& parameterX,
        juce::RangedAudioParameter& parameterY,
        XYPad& pad,
        juce::UndoManager* um = nullptr);

    ~XYPadAttachment() override;

    XYPadAttachment(XYPadAttachment const& other)                  = delete;
    XYPadAttachment(XYPadAttachment&& other)                       = delete;
    auto operator=(XYPadAttachment const& rhs) -> XYPadAttachment& = delete;
    auto operator=(XYPadAttachment&& rhs) -> XYPadAttachment&      = delete;

    /// \brief Call this after setting up your slider in the case where you
    /// need to do extra setup after constructing this attachment.
    void sendInitialUpdate();

private:
    auto xypadChanged(XYPad* pad, juce::Point<float> position) -> void override;
    auto xypadDragStarted(XYPad* pad) -> void override;
    auto xypadDragEnded(XYPad* pad) -> void override;

    auto setPosition(float newValue, bool isX) -> void;

    XYPad& _pad;
    juce::ParameterAttachment _attachmentX;
    juce::ParameterAttachment _attachmentY;
    juce::Point<float> _lastPosition {};
    bool _ignoreCallbacks = false;
    bool _isDragging { false };
};
} // namespace neo
