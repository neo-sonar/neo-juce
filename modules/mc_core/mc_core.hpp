/*
 BEGIN_JUCE_MODULE_DECLARATION

 ID:            mc_core
 vendor:        mc
 version:       0.1.0
 name:          Modern Circuits JUCE Core module
 description:   Core JUCE extensions and utilities.
 dependencies:  juce_core, juce_events

 END_JUCE_MODULE_DECLARATION
 */

#ifndef MODERN_CIRCUITS_JUCE_MODULES_MC_CORE_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_MC_CORE_HPP

#ifndef USE_MC_CORE
#define USE_MC_CORE 1
#endif

#include <juce_core/juce_core.h>
#include <juce_events/juce_events.h>

#include "fmt/chrono.h"
#include "fmt/format.h"

#include "text/format.hpp"
#include "text/string_utils.hpp"

#include "javascript/json_utils.hpp"
#include "math/range_utils.hpp"
#include "thread/thread_safe_queue.hpp"
#include "time/time_utils.hpp"

#include "thread/background_process.hpp"

#endif  // MODERN_CIRCUITS_JUCE_MODULES_MC_CORE_HPP
