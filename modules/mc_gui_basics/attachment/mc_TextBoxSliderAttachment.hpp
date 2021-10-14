#ifndef MODERN_CIRCUITS_JUCE_MODULES_TEXT_BOX_SLIDER_ATTACHMENT_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_TEXT_BOX_SLIDER_ATTACHMENT_HPP

namespace mc {
struct TextBoxSliderValueTreeAttachment : TextBoxSlider::Listener {
    TextBoxSliderValueTreeAttachment(juce::ValueTree state,
        juce::Identifier const& id,
        TextBoxSlider& slider,
        juce::UndoManager* undoManager = nullptr);

    ~TextBoxSliderValueTreeAttachment() override;
    void sendInitialUpdate();

private:
    void setValue(float newValue);
    void textBoxSliderValueChanged(TextBoxSlider* /*slider*/) override;
    void textBoxSliderDragStarted(TextBoxSlider* /*slider*/) override;
    void textBoxSliderDragEnded(TextBoxSlider* /*slider*/) override;

    TextBoxSlider& slider_;
    ValueTreeAttachment<float> attachment_;
    bool ignoreCallbacks_ = false;
};
} // namespace mc

#endif // MODERN_CIRCUITS_JUCE_MODULES_TEXT_BOX_SLIDER_ATTACHMENT_HPP
