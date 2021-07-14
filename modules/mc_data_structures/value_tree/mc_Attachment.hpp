#ifndef MODERN_CIRCUITS_PLUGINS_ATTACHMENT_HPP
#define MODERN_CIRCUITS_PLUGINS_ATTACHMENT_HPP

namespace mc {

template <typename T>
class ValueTreeAttachment
    : private juce::ValueTree::Listener,
      private juce::AsyncUpdater {
public:
    using value_type = T;

    ValueTreeAttachment(juce::ValueTree state, juce::Identifier const& id,
        std::function<void(value_type)> parameterChangedCallback,
        juce::UndoManager* undoManager = nullptr)
        : state_ { std::move(state) }, id_ { id }, undoManager_(undoManager), setValue_(std::move(parameterChangedCallback))
    {
        jassert(state_.isValid());
        state_.addListener(this);
    }

    ~ValueTreeAttachment() override
    {
        state_.removeListener(this);
        cancelPendingUpdate();
    }

    void sendInitialUpdate() { valueTreePropertyChanged(state_, id_); }

    void setValueAsCompleteGesture(value_type value)
    {
        callIfValueChanged(value, [this](value_type f) {
            beginGesture();
            state_.setProperty(id_, f, undoManager_);
            endGesture();
        });
    }

    void beginGesture()
    {
        if (undoManager_ != nullptr) {
            undoManager_->beginNewTransaction();
        }
    }

    void setValueAsPartOfGesture(value_type value)
    {
        callIfValueChanged(value, [this](value_type f) { state_.setProperty(id_, f, undoManager_); });
    }

    void endGesture()
    {
        if (undoManager_ != nullptr) {
            undoManager_->beginNewTransaction();
        }
    }

private:
    [[nodiscard]] auto getValue() const -> value_type { return state_[id_]; }

    template <typename Callback>
    void callIfValueChanged(value_type newValue, Callback&& callback)
    {
        if (getValue() != newValue) {
            callback(newValue);
        }
    }

    void valueTreePropertyChanged(juce::ValueTree& tree, juce::Identifier const& property) override
    {
        if (property == id_) {
            lastValue_ = juce::VariantConverter<value_type>::fromVar(tree[property]);
            if (juce::MessageManager::getInstance()->isThisTheMessageThread()) {
                cancelPendingUpdate();
                handleAsyncUpdate();
            } else {
                triggerAsyncUpdate();
            }
        }
    }

    void handleAsyncUpdate() override
    {
        if (setValue_ != nullptr) {
            setValue_(lastValue_);
        }
    }

    juce::ValueTree state_;
    juce::Identifier const& id_;
    value_type lastValue_;
    juce::UndoManager* undoManager_;
    std::function<void(value_type)> setValue_;

    JUCE_LEAK_DETECTOR(ValueTreeAttachment) // NOLINT
};

} // namespace mc

#endif // MODERN_CIRCUITS_PLUGINS_ATTACHMENT_HPP
