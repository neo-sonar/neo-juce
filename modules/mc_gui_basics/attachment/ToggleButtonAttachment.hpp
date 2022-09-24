#pragma once

namespace mc
{

struct ToggleButtonAttachment final
{
    ToggleButtonAttachment(juce::ValueTree state, juce::Identifier const& id, juce::Button& btn, juce::UndoManager* um);
    ~ToggleButtonAttachment() = default;

    auto sendInitialUpdate() -> void;

private:
    auto setToggleState(bool newToggleState) -> void;

    juce::Button& _button;
    ValueTreeAttachment<bool> _attachment;
    bool _ignoreCallbacks = false;
};

}  // namespace mc
