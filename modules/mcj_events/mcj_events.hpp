// SPDX-License-Identifier: BSL-1.0

/*
BEGIN_JUCE_MODULE_DECLARATION

    ID:                 mcj_events
    vendor:             Modern Circuits
    version:            0.1.0
    name:               Modern Circuits JUCE Events module
    description:        Events JUCE extensions and utilities.
    dependencies:       juce_events, mcj_core
    website:            http://github.com/ModernCircuits/mc-juce
    license:            BSL-1.0
    minimumCppStandard: 17

END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_MCJ_EVENTS
    #define USE_MCJ_EVENTS
#endif

#include <juce_events/juce_events.h>
#include <mcj_core/mcj_core.hpp>

#include "thread/BackgroundProcess.hpp"
