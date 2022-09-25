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

#ifndef USE_MC_AUDIO_PROCESSORS
    #define USE_MC_AUDIO_PROCESSORS
#endif

#include <juce_audio_processors/juce_audio_processors.h>
#include <mcj_gui_basics/mcj_gui_basics.hpp>

#include "attachment/RadioGroupAttachment.hpp"
#include "attachment/XYPadAttachment.hpp"
#include "parameter/AudioProcessorValueTreeState.hpp"
#include "parameter/TextValueConverters.hpp"
#include "parameter/TrueFalseTextConverter.hpp"
#include "parameter/makeParameter.hpp"
#include "processors/BusesLayout.hpp"
