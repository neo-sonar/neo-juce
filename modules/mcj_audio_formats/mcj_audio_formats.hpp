/*
BEGIN_JUCE_MODULE_DECLARATION

    ID:                 mcj_audio_formats
    vendor:             Modern Circuits
    version:            0.1.0
    name:               Modern Circuits JUCE Audio basics module
    description:        Audio basics JUCE extensions and utilities.
    dependencies:       juce_audio_formats, mcj_audio_basics
    website:            http://github.com/ModernCircuits/mc-juce
    license:            GPL/Commercial
    minimumCppStandard: 17

END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_MCJ_AUDIO_FORMATS
    #define USE_MCJ_AUDIO_FORMATS
#endif

#include <juce_audio_formats/juce_audio_formats.h>
#include <mcj_audio_basics/mcj_audio_basics.hpp>

#include "audio_file/load.hpp"
