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

#ifndef MODERN_CIRCUITS_JUCE_MODULES_MC_METERS_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_MC_METERS_HPP

#ifndef USE_MC_METERS
#define USE_MC_METERS 1
#endif

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_events/juce_events.h>
#include <juce_gui_basics/juce_gui_basics.h>

#include <atomic>
#include <numeric>
#include <vector>

#include "LevelMeter/LevelMeterSource.h"

#include "LevelMeter/LevelMeter.h"
#include "Visualisers/OutlineBuffer.h"
#include "Visualisers/StereoFieldBuffer.h"
#include "Visualisers/StereoFieldComponent.h"

#endif