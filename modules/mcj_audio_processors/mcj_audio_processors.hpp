/*
BEGIN_JUCE_MODULE_DECLARATION

    ID:                 mcj_audio_processors
    vendor:             Modern Circuits
    version:            0.1.0
    name:               Modern Circuits JUCE Audio Processors module
    description:        Audio Processors JUCE extensions and utilities.
    dependencies:       juce_audio_processors, mcj_gui_basics
    website:            http://github.com/ModernCircuits/mc-juce
    license:            GPL/Commercial
    minimumCppStandard: 17

END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_MCJ_AUDIO_PROCESSORS
    #define USE_MCJ_AUDIO_PROCESSORS
#endif

#include <juce_audio_processors/juce_audio_processors.h>
#include <mcj_gui_basics/mcj_gui_basics.hpp>

#include "attachment/radio_group_attachment.hpp"
#include "attachment/xypad_attachment.hpp"
#include "parameter/audio_processor_value_tree_state.hpp"
#include "parameter/make_parameter.hpp"
#include "processors/buses_layout.hpp"
#include "text_value_converter/active_text_converter.hpp"
#include "text_value_converter/frequency_text_converter.hpp"
#include "text_value_converter/gain_text_converter.hpp"
#include "text_value_converter/invert_phase_text_converter.hpp"
#include "text_value_converter/milliseconds_text_converter.hpp"
#include "text_value_converter/percent_text_converter.hpp"
#include "text_value_converter/quality_text_converter.hpp"
#include "text_value_converter/ratio_or_gate_text_converter.hpp"
#include "text_value_converter/ratio_or_limiter_text_converter.hpp"
#include "text_value_converter/seconds_text_converter.hpp"
#include "text_value_converter/true_false_text_converter.hpp"
