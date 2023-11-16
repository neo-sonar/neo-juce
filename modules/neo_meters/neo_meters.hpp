/*
BEGIN_JUCE_MODULE_DECLARATION

    ID:                 neo_meters
    vendor:             neo-sonar
    version:            0.1.0
    name:               Meters
    description:        Audio modulators, routing matrix & utilities.
    dependencies:       juce_audio_basics, neo_dsp
    website:            http://github.com/neo-sonar/neo-juce
    license:            GPL/Commercial
    minimumCppStandard: 20

END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_MC_METERS
    #define USE_MC_METERS
#endif

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_events/juce_events.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <neo_dsp/neo_dsp.hpp>

#include "level_meter/level_meter_source.hpp"

#include "level_meter/level_meter.hpp"
#include "visualisers/outline_buffer.hpp"
#include "visualisers/stereo_field_buffer.hpp"
#include "visualisers/stereo_field_component.hpp"

#include "analyzer/down_sampling_analyzer.hpp"
#include "analyzer/histogram_source.hpp"
#include "analyzer/oscilloscope_source.hpp"
#include "analyzer/spectrum_source.hpp"
#include "waveform/waveform_source.hpp"

#include "analyzer/histogram.hpp"
#include "analyzer/oscilloscope.hpp"
#include "analyzer/spectrum.hpp"
#include "waveform/waveform.hpp"
