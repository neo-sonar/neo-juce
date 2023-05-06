// SPDX-License-Identifier: BSL-1.0

/*
BEGIN_JUCE_MODULE_DECLARATION

    ID:                 mc_events
    vendor:             Modern Circuits
    version:            0.1.0
    name:               Modern Circuits JUCE Events module
    description:        Events JUCE extensions and utilities.
    dependencies:       juce_events, mc_core
    website:            http://github.com/ModernCircuits/mc-juce
    license:            BSL-1.0
    minimumCppStandard: 20

END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_MC_EVENTS
    #define USE_MC_EVENTS
#endif

#include <juce_events/juce_events.h>
#include <mc_core/mc_core.hpp>

#include "thread/BackgroundProcess.hpp"
