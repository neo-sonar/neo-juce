#pragma once

namespace neo {

class TwoValueSliderAttachment : private juce::Slider::Listener, private juce::Value::Listener {
public:
    TwoValueSliderAttachment(juce::ValueTree const& state,
        juce::Identifier const& idMin,
        juce::Identifier const& idMax,
        juce::Slider& slider,
        juce::UndoManager* undoManager = nullptr);
    ~TwoValueSliderAttachment() override;

    auto sendInitialUpdate() -> void;

private:
    auto setMinValue(float newValue) -> void;
    auto setMaxValue(float newValue) -> void;

    auto valueChanged(juce::Value& value) -> void override;

    auto sliderValueChanged(juce::Slider* slider) -> void override;
    auto sliderDragStarted(juce::Slider* slider) -> void override;
    auto sliderDragEnded(juce::Slider* slider) -> void override;

    juce::Slider& _slider;

    juce::Value& _minValue;
    ValueTreeAttachment<float> _minAttachment;
    bool _ignoreCallbacksMin = false;

    juce::Value& _maxValue;
    ValueTreeAttachment<float> _maxAttachment;
    bool _ignoreCallbacksMax = false;
};

} // namespace neo
