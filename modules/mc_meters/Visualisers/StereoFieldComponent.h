#pragma once

namespace foleys
{

/** @addtogroup ff_meters */
/*@{*/

/**
 \class StereoFieldComponent

 This class implements a circular buffer to buffer audio samples.
 At any time the GUI can ask for a stereo field visualisation of
 two neightbouring channels.
 */
class StereoFieldComponent : public juce::Component
{
public:
    enum
    {
        GonioMeter = 0,
        StereoField
    };

    enum ColourIds
    {
        backgroundColour = 0x2200101, /**< Colour for the numbers etc. */
        borderColour,                 /**< Colour for the numbers etc. */
        outlineColour,                /**< Colour for the numbers etc. */
        gonioColour,                  /**< Colour for the numbers etc. */
        currentValuesColour,          /**< Colour for the numbers etc. */
        maxValuesColour               /**< Colour for the numbers etc. */
    };

    class LookAndFeelMethods
    {
    public:
        virtual ~LookAndFeelMethods() = default;

        virtual void setupDefaultStereoFieldColours() = 0;

        virtual void drawGonioBackground(juce::Graphics& g, juce::Rectangle<float> bounds, float margin, float border)
            = 0;

        virtual void drawGonioMeter(juce::Graphics& g, juce::Rectangle<float> bounds,
                                    const StereoFieldBuffer<float>& stereoBuffer, int leftIdx, int rightIdx)
            = 0;

        virtual void drawStereoFieldBackground(juce::Graphics& g, juce::Rectangle<float> bounds, float margin,
                                               float border)
            = 0;

        virtual void drawStereoField(juce::Graphics& g, juce::Rectangle<float> bounds, const StereoFieldBuffer<float>&,
                                     int leftIdx = 0, int rightIdx = 1)
            = 0;
    };

    explicit StereoFieldComponent(StereoFieldBuffer<float>& stereo) : stereoBuffer_(stereo) { }

    void paint(juce::Graphics& g) override
    {
        juce::Graphics::ScopedSaveState saved(g);

        if (auto* lnf = dynamic_cast<StereoFieldComponent::LookAndFeelMethods*>(&getLookAndFeel()))
        {
            if (type_ == GonioMeter)
            {
                auto bounds = getLocalBounds().toFloat();
                lnf->drawGonioBackground(g, bounds, margin_, border_);
                lnf->drawGonioMeter(g, bounds.reduced(margin_), stereoBuffer_, 0, 1);
            }
            else if (type_ == StereoField)
            {
                auto bounds = getLocalBounds().toFloat();
                lnf->drawStereoFieldBackground(g, bounds, margin_, border_);
                lnf->drawStereoField(g, bounds.reduced(margin_), stereoBuffer_, 0, 1);
            }
        }
        else
        {
            // This LookAndFeel is missing the StereoFieldComponent::LookAndFeelMethods.
            // If you work with the default LookAndFeel, set an instance of
            // LevelMeterLookAndFeel as LookAndFeel of this component.
            //
            // If you write a LookAndFeel from scratch, inherit also
            // StereoFieldComponent::LookAndFeelMethods
            jassertfalse;
        }
    }

private:
    StereoFieldBuffer<float>& stereoBuffer_;
    int type_ = GonioMeter;

    float margin_ = 5.0f;
    float border_ = 2.0f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(StereoFieldComponent)  // NOLINT
};
/*@}*/
}  // namespace foleys
