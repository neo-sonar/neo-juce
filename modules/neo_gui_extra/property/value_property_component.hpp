#pragma once

namespace neo {

struct ValuePropertyComponent : juce::PropertyComponent, private juce::Value::Listener {

    ValuePropertyComponent(juce::Value value, juce::String const& name);
    ~ValuePropertyComponent() override = default;

    [[nodiscard]] auto value() -> juce::Value&;
    [[nodiscard]] auto value() const -> juce::Value const&;

private:
    auto valueChanged(juce::Value& /*value*/) -> void override;

    juce::Value _value;
};

} // namespace neo
