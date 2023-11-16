#pragma once

namespace neo {

SliderListener::SliderListener(juce::Slider& slider) : _slider { slider } { _slider.addListener(this); }

SliderListener::~SliderListener() { _slider.removeListener(this); }

auto SliderListener::sliderValueChanged(juce::Slider* slider) -> void
{
    jassert(slider == &_slider);
    juce::ignoreUnused(slider);

    if (onValueChanged) { onValueChanged(); }
}

auto SliderListener::sliderDragStarted(juce::Slider* slider) -> void
{
    jassert(slider == &_slider);
    juce::ignoreUnused(slider);

    if (onDragStarted) { onDragStarted(); }
}

auto SliderListener::sliderDragEnded(juce::Slider* slider) -> void
{
    jassert(slider == &_slider);
    juce::ignoreUnused(slider);

    if (onDragEnded) { onDragEnded(); }
}

} // namespace neo
