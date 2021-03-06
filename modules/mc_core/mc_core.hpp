/*
 ==============================================================================
 BEGIN_JUCE_MODULE_DECLARATION

 ID:            mc_core
 vendor:        Modern Circuits
 version:       0.1.0
 name:          Core
 description:   Core JUCE extensions and utilities.
 dependencies:  juce_gui_extra, juce_events, juce_dsp
 website:       https://modern-circuits.com
 license:       Copyright 2019-2021 Modern Circuits. All rights reserved.

 END_JUCE_MODULE_DECLARATION

 ==============================================================================

 @defgroup mc_core

 ==============================================================================
 */

#ifndef MODERN_CIRCUITS_JUCE_MODULES_MC_CORE_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_MC_CORE_HPP

#ifndef USE_MC_CORE
#define USE_MC_CORE 1
#endif

#include <juce_dsp/juce_dsp.h>
#include <juce_events/juce_events.h>
#include <juce_gui_extra/juce_gui_extra.h>

#include "fmt/chrono.h"
#include "fmt/format.h"

#include "core/format.hpp"

#endif  // MODERN_CIRCUITS_JUCE_MODULES_MC_CORE_HPP
