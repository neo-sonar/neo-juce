/*
BEGIN_JUCE_MODULE_DECLARATION

    ID:                 neo_audio_formats
    vendor:             neo-sonar
    version:            0.1.0
    name:               neo-sonar JUCE Audio basics module
    description:        Audio basics JUCE extensions and utilities.
    dependencies:       juce_audio_formats, neo_audio_basics
    website:            http://github.com/neo-sonar/neo-juce
    license:            GPL/Commercial
    minimumCppStandard: 20

END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_MC_AUDIO_FORMATS
    #define USE_MC_AUDIO_FORMATS
#endif

#include <juce_audio_formats/juce_audio_formats.h>
#include <neo_audio_basics/neo_audio_basics.hpp>

#include "audio_file/load.hpp"
