// SPDX-License-Identifier: BSL-1.0

/*
BEGIN_JUCE_MODULE_DECLARATION

    ID:                 mcj_meters
    vendor:             Modern Circuits
    version:            0.1.0
    name:               Meters
    description:        Audio modulators, routing matrix & utilities.
    dependencies:       juce_audio_basics, mcj_dsp
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
#include <mcj_dsp/mcj_dsp.hpp>

#include "level_meter/level_meter_source.hpp"

#include "level_meter/level_meter.hpp"
#include "visualisers/outline_buffer.hpp"
#include "visualisers/stereo_field_buffer.hpp"
#include "visualisers/stereo_field_component.hpp"

#include "analyzer/down_sampling_analyzer.hpp"
#include "analyzer/histogram_source.hpp"
#include "analyzer/oscilloscope_source.hpp"
#include "analyzer/spectrum_source.hpp"

#include "analyzer/histogram.hpp"
#include "analyzer/oscilloscope.hpp"
#include "analyzer/spectrum.hpp"
