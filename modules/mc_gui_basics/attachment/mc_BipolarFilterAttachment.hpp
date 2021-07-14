#ifndef MODERN_CIRCUITS_JUCE_MODULES_mc_BipolarFilter_ATTACHMENT_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_mc_BipolarFilter_ATTACHMENT_HPP

namespace mc {

class BipolarFilterValueTreeAttachment : private BipolarFilter::Listener {
public:
    BipolarFilterValueTreeAttachment(juce::ValueTree state, juce::Identifier const& id, BipolarFilter& slider,
        juce::UndoManager* undoManager = nullptr);

    ~BipolarFilterValueTreeAttachment() override;
    void sendInitialUpdate();

private:
    void setValue(float newValue);
    void bipolarFilterValueChanged(BipolarFilter* /*slider*/) override;
    void bipolarFilterDragStarted(BipolarFilter* /*slider*/) override;
    void bipolarFilterDragEnded(BipolarFilter* /*slider*/) override;

    BipolarFilter& slider_;
    ValueTreeAttachment<float> attachment_;
    bool ignoreCallbacks_ = false;
};

} // namespace mc

#endif // MODERN_CIRCUITS_JUCE_MODULES_mc_BipolarFilter_ATTACHMENT_HPP
