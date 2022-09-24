#pragma once

namespace mc {

struct SliderListener final : juce::Slider::Listener {
    explicit SliderListener(juce::Slider& slider);
    ~SliderListener() override;

    SliderListener(SliderListener const&) = delete;
    SliderListener(SliderListener&&)      = delete;

    auto operator=(SliderListener const&) -> SliderListener& = delete;
    auto operator=(SliderListener&&) -> SliderListener&      = delete;

    std::function<void()> onValueChanged {};
    std::function<void()> onDragStarted {};
    std::function<void()> onDragEnded {};

private:
    auto sliderValueChanged(juce::Slider* slider) -> void override;
    auto sliderDragStarted(juce::Slider* slider) -> void override;
    auto sliderDragEnded(juce::Slider* slider) -> void override;

    juce::Slider& _slider;
};

} // namespace mc