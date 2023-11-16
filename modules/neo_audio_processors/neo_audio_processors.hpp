/*
BEGIN_JUCE_MODULE_DECLARATION

    ID:                 neo_audio_processors
    vendor:             neo-sonar
    version:            0.1.0
    name:               neo-sonar JUCE Audio Processors module
    description:        Audio Processors JUCE extensions and utilities.
    dependencies:       juce_audio_processors, neo_gui_basics
    website:            http://github.com/neo-sonar/neo-juce
    license:            GPL/Commercial
    minimumCppStandard: 20

END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_MC_AUDIO_PROCESSORS
    #define USE_MC_AUDIO_PROCESSORS
#endif

#include <juce_audio_processors/juce_audio_processors.h>
#include <neo_gui_basics/neo_gui_basics.hpp>

#include "attachment/radio_group_attachment.hpp"
#include "attachment/xypad_attachment.hpp"
#include "parameter/audio_processor_value_tree_state.hpp"
#include "parameter/make_parameter.hpp"
#include "parameter/text_value_converter.hpp"
#include "processors/buses_layout.hpp"
