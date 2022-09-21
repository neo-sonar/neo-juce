/*
 BEGIN_JUCE_MODULE_DECLARATION

 ID:            mc_audio_processors
 vendor:        mc
 version:       0.1.0
 name:          Modern Circuits JUCE Events module
 description:   Events JUCE extensions and utilities.
 dependencies:  juce_audio_processors, mc_dsp

 END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_MC_AUDIO_PROCESSORS
    #define USE_MC_AUDIO_PROCESSORS
#endif

#include <juce_audio_processors/juce_audio_processors.h>
#include <mc_dsp/mc_dsp.hpp>

#include "parameter/AudioProcessorValueTreeState.hpp"
