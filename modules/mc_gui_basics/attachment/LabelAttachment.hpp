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
        : state_ { state }
        , id_ { id }
        , label_ { label }
        , attachment_ { state, id, [this](auto f) { setValue(std::move(f)); }, undoManager }
    {
        sendInitialUpdate();
        state_.addListener(this);
    }

    ~LabelValueTreeAttachment() override { state_.removeListener(this); }

    void sendInitialUpdate() { attachment_.sendInitialUpdate(); }

private:
    auto setValue(value_type content) -> void
    {
        auto text = juce::String { content };
        juce::ScopedValueSetter<bool> svs(ignoreCallbacks_, true);
        label_.setText(text, juce::dontSendNotification);
    }

    void valueTreePropertyChanged(juce::ValueTree& tree, juce::Identifier const& id) override
    {
        if (tree == state_ && id == id_) {
            if (ignoreCallbacks_) { return; }
            attachment_.setValueAsCompleteGesture(tree[id]);
        }
    }

    juce::ValueTree state_;
    juce::Identifier const& id_;
    juce::Label& label_;
    ValueTreeAttachment<value_type> attachment_;
    bool ignoreCallbacks_ = false;
};

template <typename T = juce::String>
struct ValueTreeLabel : juce::Component {
    using value_type = T;

    explicit ValueTreeLabel(juce::CachedValue<value_type>& value)
        : value_ { value }
        , attachment_ { value_.getValueTree(), value_.getPropertyID(), label_, value_.getUndoManager() }
    {
        addAndMakeVisible(label_);
    }

    ~ValueTreeLabel() override = default;

    auto resized() -> void override { label_.setBounds(getLocalBounds()); }

private:
    juce::CachedValue<value_type>& value_;
    juce::Label label_;
    LabelValueTreeAttachment<value_type> attachment_;
};
} // namespace mc

#endif // MODERN_CIRCUITS_JUCE_MODULES_LABEL_ATTACHMENT_HPP
