/*
 BEGIN_JUCE_MODULE_DECLARATION

 ID:            mcj_events
 vendor:        mc
 version:       0.1.0
 name:          Modern Circuits JUCE Events module
 description:   Events JUCE extensions and utilities.
 dependencies:  juce_events, mcj_core

 END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_MC_EVENTS
    #define USE_MC_EVENTS
#endif

#include <juce_events/juce_events.h>
#include <mcj_core/mcj_core.hpp>

#include "thread/BackgroundProcess.hpp"
