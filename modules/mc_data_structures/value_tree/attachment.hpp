#ifndef MODERN_CIRCUITS_PLUGINS_ATTACHMENT_HPP
#define MODERN_CIRCUITS_PLUGINS_ATTACHMENT_HPP

namespace mc
{
template<typename T>
class ValueTreeAttachment
    : private juce::ValueTree::Listener
    , private juce::AsyncUpdater
{
public:
    using value_type = T;

    ValueTreeAttachment(juce::ValueTree state, juce::Identifier const& id,
                        std::function<void(value_type)> parameterChangedCallback,
                        juce::UndoManager* undoManager = nullptr)
        : state_ {state}, id_ {id}, undoManager_(undoManager), setValue_(std::move(parameterChangedCallback))
    {
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
        if (undoManager_ != nullptr) { undoManager_->beginNewTransaction(); }
    }

    void setValueAsPartOfGesture(value_type value)
    {
        callIfValueChanged(value, [this](value_type f) { state_.setProperty(id_, f, undoManager_); });
    }

    void endGesture()
    {
        if (undoManager_ != nullptr) { undoManager_->beginNewTransaction(); }
    }

private:
    [[nodiscard]] auto getValue() const -> value_type { return state_[id_]; }

    template<typename Callback>
    void callIfValueChanged(value_type newValue, Callback&& callback)
    {
        if (getValue() != newValue) callback(newValue);
    }

    void valueTreePropertyChanged(juce::ValueTree& tree, juce::Identifier const& property) override
    {
        if (property == id_)
        {
            lastValue_ = juce::VariantConverter<value_type>::fromVar(tree[property]);
            if (juce::MessageManager::getInstance()->isThisTheMessageThread())
            {
                cancelPendingUpdate();
                handleAsyncUpdate();
            }
            else
            {
                triggerAsyncUpdate();
            }
        }
    }

    void handleAsyncUpdate() override
    {
        if (setValue_ != nullptr) { setValue_(lastValue_); }
    }

    juce::ValueTree state_;
    juce::Identifier const& id_;
    value_type lastValue_;
    juce::UndoManager* undoManager_;
    std::function<void(value_type)> setValue_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ValueTreeAttachment)
};

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

template<typename T>
class LabelValueTreeAttachment : public juce::ValueTree::Listener
{
public:
    using value_type = T;
    LabelValueTreeAttachment(juce::ValueTree state, juce::Identifier const& id, juce::Label& label,
                             juce::UndoManager* undoManager = nullptr)
        : state_ {state}
        , id_ {id}
        , label_ {label}
        , attachment_ {state, id, [this](auto f) { setValue(std::move(f)); }, undoManager}
    {
        sendInitialUpdate();
        state_.addListener(this);
    }

    ~LabelValueTreeAttachment() override { state_.removeListener(this); }

    void sendInitialUpdate() { attachment_.sendInitialUpdate(); }

private:
    auto setValue(value_type content) -> void
    {
        auto text = juce::String {content};
        juce::ScopedValueSetter<bool> svs(ignoreCallbacks_, true);
        label_.setText(text, juce::dontSendNotification);
    }

    void valueTreePropertyChanged(juce::ValueTree& tree, juce::Identifier const& id) override
    {
        if (tree == state_ && id == id_)
        {
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

template<typename T = juce::String>
class ValueTreeLabel : public juce::Component
{
public:
    using value_type = T;

    explicit ValueTreeLabel(juce::CachedValue<value_type>& value)
        : value_ {value}, attachment_ {value_.getValueTree(), value_.getPropertyID(), label_, value_.getUndoManager()}
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
}  // namespace mc
#endif  // MODERN_CIRCUITS_PLUGINS_ATTACHMENT_HPP
