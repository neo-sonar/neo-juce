// SPDX-License-Identifier: BSL-1.0

/*
BEGIN_JUCE_MODULE_DECLARATION

    ID:                 mcj_meters
    vendor:             Modern Circuits
    version:            0.1.0
    name:               Meters
    description:        Audio modulators, routing matrix & utilities.
    dependencies:       juce_audio_basics, mcj_data_structures
    website:            http://github.com/ModernCircuits/mc-juce
    license:            BSL-1.0
    minimumCppStandard: 17

END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_MC_METERS
    #define USE_MC_METERS
#endif

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_events/juce_events.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <mcj_data_structures/mcj_data_structures.hpp>

#include "LevelMeter/LevelMeterSource.hpp"

#include "LevelMeter/LevelMeter.hpp"
#include "Visualisers/OutlineBuffer.hpp"
#include "Visualisers/StereoFieldBuffer.hpp"
#include "Visualisers/StereoFieldComponent.hpp"
