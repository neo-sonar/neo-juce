#ifndef MODERN_CIRCUITS_JUCE_MODULES_LABEL_ATTACHMENT_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_LABEL_ATTACHMENT_HPP

namespace mc {

template <typename T>
struct LabelValueTreeAttachment : juce::ValueTree::Listener {
    using value_type = T;
    LabelValueTreeAttachment(juce::ValueTree state,
        juce::Identifier const& id,
        juce::Label& label,
        juce::UndoManager* undoManager = nullptr)
        : _state { state }
        , _id { id }
        , _label { label }
        , _attachment { state, id, [this](auto f) { setValue(std::move(f)); }, undoManager }
    {
        sendInitialUpdate();
        _state.addListener(this);
    }

    ~LabelValueTreeAttachment() override { _state.removeListener(this); }

    void sendInitialUpdate() { _attachment.sendInitialUpdate(); }

private:
    auto setValue(value_type content) -> void
    {
        auto text = juce::String { content };
        juce::ScopedValueSetter<bool> svs(_ignoreCallbacks, true);
        _label.setText(text, juce::dontSendNotification);
    }

    void valueTreePropertyChanged(juce::ValueTree& tree, juce::Identifier const& id) override
    {
        if (tree == _state && id == _id) {
            if (_ignoreCallbacks) { return; }
            _attachment.setValueAsCompleteGesture(tree[id]);
        }
    }

    juce::ValueTree _state;
    juce::Identifier const& _id;
    juce::Label& _label;
    ValueTreeAttachment<value_type> _attachment;
    bool _ignoreCallbacks = false;
};

template <typename T = juce::String>
struct ValueTreeLabel : juce::Component {
    using value_type = T;

    explicit ValueTreeLabel(juce::CachedValue<value_type>& value)
        : _value { value }
        , _attachment { _value.getValueTree(), _value.getPropertyID(), _label, _value.getUndoManager() }
    {
        addAndMakeVisible(_label);
    }

    ~ValueTreeLabel() override = default;

    auto resized() -> void override { _label.setBounds(getLocalBounds()); }

private:
    juce::CachedValue<value_type>& _value;
    juce::Label _label;
    LabelValueTreeAttachment<value_type> _attachment;
};
} // namespace mc

#endif // MODERN_CIRCUITS_JUCE_MODULES_LABEL_ATTACHMENT_HPP
