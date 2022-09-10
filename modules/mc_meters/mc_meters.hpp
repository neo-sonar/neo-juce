/*
 BEGIN_JUCE_MODULE_DECLARATION

 ID:            mc_meters
 vendor:        mc
 version:       0.1.0
 name:          Meters
 description:   Audio modulators, routing matrix & utilities.
 dependencies:  juce_audio_basics, mc_data_structures

 END_JUCE_MODULE_DECLARATION
 */

#pragma once

#ifndef USE_MC_METERS
    #define USE_MC_METERS
#endif

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_events/juce_events.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <mc_data_structures/mc_data_structures.hpp>

#include "LevelMeter/LevelMeterSource.hpp"

#include "LevelMeter/LevelMeter.hpp"
#include "Visualisers/OutlineBuffer.hpp"
#include "Visualisers/StereoFieldBuffer.hpp"
#include "Visualisers/StereoFieldComponent.hpp"
