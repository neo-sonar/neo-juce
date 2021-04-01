
#pragma once

namespace foleys
{

class LevelMeterSource;

/** @addtogroup ff_meters */
/*@{*/

/**
   \class LevelMeterLookAndFeel
   \brief Convenience LookAndFeel which derives from LookAndFeel_V3 and LevelMeter::LookAndFeelMethods

   This is the shortcut, to get a component going without inheriting any LookAndFeel class.
   If you write your own LookAndFeel, you can include ff_meters_LookAndFeelMethods.h inside your LookAndFeel:

   \code{.cpp}
       class MyLookAndFeel : public LookAndFeel_V4, LevelMeter::LookAndFeelMethods
       {
           public:

               #include "ff_meters_LookAndFeelMethods.h"

               // ...

       };
   \endcode
*/
class LevelMeterLookAndFeel
    : public juce::LookAndFeel_V3
    , public LevelMeter::LookAndFeelMethods
    , public StereoFieldComponent::LookAndFeelMethods
{
public:
    LevelMeterLookAndFeel()
    {
        setupDefaultMeterColours();

        setupDefaultStereoFieldColours();
    }

    ~LevelMeterLookAndFeel() override = default;

// do this include inside the class to get the default implementation instead of copying it there
#include "LevelMeterLookAndFeelMethods.h"

// and the same to get the default sound field implementation instead of copying it there
#include "SoundFieldLookAndFeelMethods.h"
};

/*@}*/

}  // end namespace foleys
