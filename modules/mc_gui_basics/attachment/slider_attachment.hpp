#ifndef MODERN_CIRCUITS_JUCE_MODULES_SLIDER_ATTACHMENT_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_SLIDER_ATTACHMENT_HPP

namespace mc
{
class SliderValueTreeAttachment : private juce::Slider::Listener
{
public:
    SliderValueTreeAttachment(juce::ValueTree state, juce::Identifier const& id, juce::Slider& slider,
                              juce::UndoManager* undoManager = nullptr)
        : slider_ {slider}, attachment_ {state, id, [this](auto f) { setValue(f); }, undoManager}
    {
        sendInitialUpdate();
        slider_.valueChanged();
        slider_.addListener(this);
    }

    ~SliderValueTreeAttachment() override { slider_.removeListener(this); }

    void sendInitialUpdate() { attachment_.sendInitialUpdate(); }

private:
    void setValue(float newValue)
    {
        juce::ScopedValueSetter<bool> svs(ignoreCallbacks_, true);
        slider_.setValue(newValue, juce::sendNotificationSync);
    }
    void sliderValueChanged(juce::Slider* /*slider*/) override
    {
        if (ignoreCallbacks_ || juce::ModifierKeys::currentModifiers.isRightButtonDown()) { return; }
        attachment_.setValueAsPartOfGesture(static_cast<float>(slider_.getValue()));
    }

    void sliderDragStarted(juce::Slider* /*slider*/) override { attachment_.beginGesture(); }
    void sliderDragEnded(juce::Slider* /*slider*/) override { attachment_.endGesture(); }

    juce::Slider& slider_;
    ValueTreeAttachment<float> attachment_;
    bool ignoreCallbacks_ = false;
};
}  // namespace mc
#endif  // MODERN_CIRCUITS_JUCE_MODULES_SLIDER_ATTACHMENT_HPP
