#pragma once

namespace neo {

struct PlaceholderSpec {
    juce::Colour backgroundColor {};
    juce::Colour textColor {};
    juce::String text {};
};

struct Placeholder final : juce::Component {
    using Spec = PlaceholderSpec;

    explicit Placeholder(juce::Colour color, juce::String text = {});
    explicit Placeholder(Spec spec);

    ~Placeholder() override = default;

    auto paint(juce::Graphics& g) -> void override;

private:
    Spec _spec;
};

} // namespace neo
