#pragma once

namespace neo {
struct SliderValueTreeAttachment : juce::Slider::Listener {
    SliderValueTreeAttachment(juce::ValueTree state,
        juce::Identifier const& id,
        juce::Slider& slider,
        juce::UndoManager* undoManager = nullptr);
    ~SliderValueTreeAttachment() override;
    void sendInitialUpdate();

private:
    void setValue(float newValue);

    void sliderValueChanged(juce::Slider* /*slider*/) override;
    void sliderDragStarted(juce::Slider* /*slider*/) override;
    void sliderDragEnded(juce::Slider* /*slider*/) override;

    juce::Slider& _slider;
    ValueTreeAttachment<float> _attachment;
    bool _ignoreCallbacks = false;
};
} // namespace neo
