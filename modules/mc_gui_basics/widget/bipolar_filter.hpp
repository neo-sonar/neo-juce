#ifndef MODERN_CIRCUITS_PLUGINS_BIPOLAR_FILTER_HPP
#define MODERN_CIRCUITS_PLUGINS_BIPOLAR_FILTER_HPP

namespace mc
{
class BipolarFilter : public juce::Component
{
public:
    enum ColorIDs
    {
        backgroundColor,
        lineColor,
        thumbColor,
    };

    struct Listener
    {
        virtual ~Listener() = default;

        virtual auto bipolarFilterValueChanged(BipolarFilter* bipolarFilter) -> void = 0;
        virtual auto bipolarFilterDragStarted(BipolarFilter* bipolarFilter) -> void  = 0;
        virtual auto bipolarFilterDragEnded(BipolarFilter* bipolarFilter) -> void    = 0;
    };

    BipolarFilter()           = default;
    ~BipolarFilter() override = default;

    auto setValue(double newValue) -> void;
    [[nodiscard]] auto getValue() const noexcept -> double;

    auto paint(juce::Graphics& g) -> void override;
    auto resized() -> void override;

private:
    auto mouseDown(juce::MouseEvent const& mouseEvent) -> void override;
    auto mouseDrag(juce::MouseEvent const& mouseEvent) -> void override;
    auto mouseUp(juce::MouseEvent const& mouseEvent) -> void override;

    auto startDragging() -> void;
    auto stopDragging() -> void;

    juce::Range<double> range_ {-1.0, 1.0};
    double currentValue_ {0.0};

    juce::Rectangle<float> thumbArea_ {};
    bool isDragging_ {false};

    juce::ListenerList<Listener> listeners_ {};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BipolarFilter)  // NOLINT
};
}  // namespace mc
#endif  // MODERN_CIRCUITS_PLUGINS_BIPOLAR_FILTER_HPP
