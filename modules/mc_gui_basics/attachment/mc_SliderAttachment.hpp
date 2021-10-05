#ifndef MODERN_CIRCUITS_JUCE_MODULES_SLIDER_ATTACHMENT_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_SLIDER_ATTACHMENT_HPP

namespace mc {
struct SliderValueTreeAttachment : juce::Slider::Listener {
    SliderValueTreeAttachment(juce::ValueTree state, juce::Identifier const& id, juce::Slider& slider,
        juce::UndoManager* undoManager = nullptr);
    ~SliderValueTreeAttachment() override;
    void sendInitialUpdate();

private:
    void setValue(float newValue);

    void sliderValueChanged(juce::Slider* /*slider*/) override;
    void sliderDragStarted(juce::Slider* /*slider*/) override;
    void sliderDragEnded(juce::Slider* /*slider*/) override;

    juce::Slider& slider_;
    ValueTreeAttachment<float> attachment_;
    bool ignoreCallbacks_ = false;
};
} // namespace mc
#endif // MODERN_CIRCUITS_JUCE_MODULES_SLIDER_ATTACHMENT_HPP
