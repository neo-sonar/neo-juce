#pragma once

namespace neo {

/// \brief A component to display live gain and RMS readings
///
/// This class is used to display a level reading. It supports max and RMS levels.
/// You can also set a reduction value to display, the definition of that value is up to you.
struct LevelMeter : juce::Component, juce::Timer {
    enum MeterFlags : unsigned {
        Default       = 0x0000, /**< Default is showing all channels in the LevelMeterSource without a border */
        Horizontal    = 0x0001, /**< Displays the level bars horizontally */
        Vintage       = 0x0002, /**< Switches to a special mode of old school meters (to come) */
        SingleChannel = 0x0004, /**< Display only one channel meter. \see setSelectedChannel */
        HasBorder     = 0x0008, /**< Displays a rounded border around the meter.  */
        Reduction     = 0x0010, /**< This turns the bar into a reduction bar. */
        Minimal       = 0x0020, /**< For a stereo meter */
        MaxNumber     = 0x0040  /**< To add level meter to Minimal, set this flag */
    };

    enum ColourIds {
        lmTextColour = 0x2200001, /**< Colour for the numbers etc. */
        lmTextDeactiveColour,     /**< Unused, will eventually be removed */
        lmTextClipColour,         /**< Colour to print the max number if it has clipped */
        lmTicksColour,            /**< Colour for the tick marks */
        lmOutlineColour,          /**< Colour for the frame around all */
        lmBackgroundColour,       /**< Background colour */
        lmBackgroundClipColour,   /**< This is the colour of the clip indicator if it has clipped */
        lmMeterForegroundColour,  /**< Unused, will eventually be removed */
        lmMeterOutlineColour,     /**< Colour for the outlines of meter bars etc. */
        lmMeterBackgroundColour,  /**< Background colour for the actual meter bar and the max number */
        lmMeterMaxNormalColour,   /**< Text colour for the max number, if under warn threshold */
        lmMeterMaxWarnColour,     /**< Text colour for the max number, if between warn threshold and clip threshold */
        lmMeterMaxOverColour,     /**< Text colour for the max number, if above the clip threshold */
        lmMeterGradientLowColour, /**< Colour for the meter bar under the warn threshold */
        lmMeterGradientMidColour, /**< Colour for the meter bar in the warn area */
        lmMeterGradientMaxColour, /**< Colour for the meter bar at the clip threshold */
        lmMeterReductionColour    /**< Colour for the reduction meter displayed within the meter */
    };

    /**
     These methods define a interface for the LookAndFeel class of juce.
     The LevelMeter needs a LookAndFeel, that implements these methods.
     There is a default implementation to be included in your custom LookAndFeel class, \see LookAndFeelMethods.h
     */
    struct LookAndFeelMethods {
        virtual ~LookAndFeelMethods() = default;

        /// \brief Define your default colours in this callback
        virtual void setupDefaultMeterColours() = 0;

        /// \brief Call this to create the cached ColourGradients after changing colours of the meter gradients
        virtual void updateMeterGradients() = 0;

        /// \brief Override this to change the inner rectangle in case you want to paint a border e.g.
        [[nodiscard]] virtual auto getMeterInnerBounds(juce::Rectangle<float> bounds, MeterFlags meterType) const
            -> juce::Rectangle<float>
            = 0;

        /// \brief Override this callback to define the placement of a meter channel.
        [[nodiscard]] virtual auto
        getMeterBounds(juce::Rectangle<float> bounds, MeterFlags meterType, int numChannels, int channel) const
            -> juce::Rectangle<float>
            = 0;

        /// \brief Override this callback to define the placement of the actual meter bar.
        [[nodiscard]] virtual auto getMeterBarBounds(juce::Rectangle<float> bounds, MeterFlags meterType) const
            -> juce::Rectangle<float>
            = 0;

        /// \brief Override this callback to define the placement of the tickmarks.
        /// To disable this feature return an empty rectangle.
        [[nodiscard]] virtual auto getMeterTickmarksBounds(juce::Rectangle<float> bounds, MeterFlags meterType) const
            -> juce::Rectangle<float>
            = 0;

        /// \brief Override this callback to define the placement of the clip indicator light.
        /// To disable this feature return an empty rectangle.
        [[nodiscard]] virtual auto getMeterClipIndicatorBounds(juce::Rectangle<float> bounds,
            MeterFlags meterType) const -> juce::Rectangle<float>
            = 0;

        /// \brief Override this to draw background and if wanted a frame. If the frame takes space away,
        /// it should return the reduced bounds
        virtual auto drawBackground(juce::Graphics&, MeterFlags meterType, juce::Rectangle<float> bounds)
            -> juce::Rectangle<float>
            = 0;

        /// \brief This is called to draw the actual numbers and bars on top of the static background
        virtual void drawMeterBars(juce::Graphics&,
            MeterFlags meterType,
            juce::Rectangle<float> bounds,
            LevelMeterSource const* source,
            int fixedNumChannels = -1,
            int selectedChannel  = -1)
            = 0;

        /// \brief This draws the static background of the whole level meter group with all channels
        virtual void drawMeterBarsBackground(juce::Graphics&,
            MeterFlags meterType,
            juce::Rectangle<float> bounds,
            int numChannels,
            int fixedNumChannels = -1)
            = 0;

        /// \brief This draws a group of informations representing one channel
        virtual void drawMeterChannel(juce::Graphics&,
            MeterFlags meterType,
            juce::Rectangle<float> bounds,
            LevelMeterSource const* source,
            int selectedChannel)
            = 0;

        /// \brief This draws the static backgrounds representing one channel
        virtual void drawMeterChannelBackground(juce::Graphics&, MeterFlags meterType, juce::Rectangle<float> bounds)
            = 0;

        /// \brief This callback draws the actual level bar. The background has an extra callback
        virtual void
        drawMeterBar(juce::Graphics&, MeterFlags meterType, juce::Rectangle<float> bounds, float rms, float peak)
            = 0;

        /// \brief This callback draws an reduction from top. Only triggered,
        /// if a reduction < 1.0 is set in the LevelMeterSource
        virtual void drawMeterReduction(juce::Graphics& g,
            LevelMeter::MeterFlags meterType,
            juce::Rectangle<float> bounds,
            float reduction)
            = 0;

        /// \brief This draws the background for the actual level bar
        virtual void drawMeterBarBackground(juce::Graphics&, MeterFlags meterType, juce::Rectangle<float> bounds) = 0;

        /// \brief This draws the tickmarks for the level scale. It is painted on the static background
        virtual void drawTickMarks(juce::Graphics&, MeterFlags meterType, juce::Rectangle<float> bounds) = 0;

        /// \brief This callback draws the clip indicator. The background has an extra callback
        virtual void
        drawClipIndicator(juce::Graphics&, MeterFlags meterType, juce::Rectangle<float> bounds, bool hasClipped)
            = 0;

        /// \brief This draws the background for the clip indicator LED
        virtual void drawClipIndicatorBackground(juce::Graphics&, MeterFlags meterType, juce::Rectangle<float> bounds)
            = 0;

        /// \brief Override this callback to define the placement of the max level.
        /// To disable this feature return an empty rectangle.
        [[nodiscard]] virtual auto getMeterMaxNumberBounds(juce::Rectangle<float> bounds, MeterFlags meterType) const
            -> juce::Rectangle<float>
            = 0;

        /// \brief This callback draws the number of maximum level. The background has an extra callback
        virtual void drawMaxNumber(juce::Graphics&, MeterFlags meterType, juce::Rectangle<float> bounds, float maxGain)
            = 0;

        /// \brief This draws the background for the maximum level display
        virtual void drawMaxNumberBackground(juce::Graphics&, MeterFlags meterType, juce::Rectangle<float> bounds) = 0;

        /// \brief This is called by the frontend to check, if the clip indicator was clicked (e.g. for reset)
        virtual auto hitTestClipIndicator(juce::Point<int> position,
            MeterFlags meterType,
            juce::Rectangle<float> bounds,
            LevelMeterSource const* source) const -> int
            = 0;

        /// \brief This is called by the frontend to check, if the maximum level number was clicked (e.g. for reset)
        virtual auto hitTestMaxNumber(juce::Point<int> position,
            MeterFlags meterType,
            juce::Rectangle<float> bounds,
            LevelMeterSource const* source) const -> int
            = 0;
    };

    explicit LevelMeter(MeterFlags type = HasBorder);
    ~LevelMeter() override = default;

    /// \brief Allows to change the meter's configuration by setting a combination of MeterFlags  */
    void setMeterFlags(MeterFlags type);

    /// \brief Set a LevelMeterSource to display. This separation is used, so the source can work in the processing and
    /// the  GUI can display the values.
    void setMeterSource(LevelMeterSource* src);

    /// \brief Set a specific channel to display. This is only useful, if MeterFlags::SingleChannel is set.
    void setSelectedChannel(int c);

    /// \brief If you don't know, how many channels will be in the processblock, you can set this number to avoid
    /// stretching  the width of the channels.
    void setFixedNumChannels(int numChannels);

    void setRefreshRateHz(int newRefreshRate);

    /**
     Unset the clip indicator flag for a channel. Use -1 to reset all clip indicators.
     */
    void clearClipIndicator(int channel = -1);

    /**
     Set the max level display back to -inf for a channel. Use -1 to reset all max levels.
     */
    void clearMaxLevelDisplay(int channel = -1);

    /**
     This lambda is called when the user clicks on a clip light. It is initially set to clear all clip lights
     and max level numbers.
     */
    std::function<void(LevelMeter& meter, int channel, juce::ModifierKeys mods)> onClipLightClicked;

    /**
     This lambda is called when the user clicks on a max level display. It is initially set to clear all clip lights
     and max level numbers.
     */
    std::function<void(LevelMeter& meter, int channel, juce::ModifierKeys mods)> onMaxLevelClicked;

private:
    void paint(juce::Graphics& g) override;
    void resized() override;
    void timerCallback() override;
    void mouseDown(juce::MouseEvent const& event) override;
    void parentHierarchyChanged() override;
    void lookAndFeelChanged() override;

    JUCE_LEAK_DETECTOR(LevelMeter) // NOLINT

    juce::WeakReference<LevelMeterSource> _source;
    LevelMeter::LookAndFeelMethods* _lnf = nullptr;

    int _selectedChannel  = -1;
    int _fixedNumChannels = -1;
    MeterFlags _meterType = HasBorder;
    int _refreshRate      = 30;
};

inline auto operator|(LevelMeter::MeterFlags a, LevelMeter::MeterFlags b) -> LevelMeter::MeterFlags
{
    return static_cast<LevelMeter::MeterFlags>(static_cast<unsigned>(a) | static_cast<unsigned>(b));
}

} // namespace neo
