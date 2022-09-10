/*
 BEGIN_JUCE_MODULE_DECLARATION

 ID:            mc_events
 vendor:        mc
 version:       0.1.0
 name:          Modern Circuits JUCE Events module
 description:   Events JUCE extensions and utilities.
 dependencies:  juce_events, mc_core

 END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_MC_CORE
    #define USE_MC_CORE
#endif

#include <juce_events/juce_events.h>
#include <mc_core/mc_core.hpp>

#include "thread/BackgroundProcess.hpp"
