// SPDX-License-Identifier: BSL-1.0

/*
BEGIN_JUCE_MODULE_DECLARATION

    ID:                 neo_events
    vendor:             neo-sonar
    version:            0.1.0
    name:               neo-sonar JUCE Events module
    description:        Events JUCE extensions and utilities.
    dependencies:       juce_events, neo_core
    website:            http://github.com/neo-sonar/neo-juce
    license:            BSL-1.0
    minimumCppStandard: 20

END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_MC_EVENTS
    #define USE_MC_EVENTS
#endif

#include <juce_events/juce_events.h>
#include <neo_core/neo_core.hpp>

#include "thread/BackgroundProcess.hpp"
