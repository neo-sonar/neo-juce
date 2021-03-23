/*
 BEGIN_JUCE_MODULE_DECLARATION

 ID:            mc_core
 vendor:        mc
 version:       0.1.0
 name:          Modern Circuits JUCE Core module
 description:   Core JUCE extensions and utilities.
 dependencies:  juce_core, juce_events, juce_audio_basics, mc_external

 END_JUCE_MODULE_DECLARATION
 */

#ifndef MODERN_CIRCUITS_JUCE_MODULES_MC_CORE_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_MC_CORE_HPP

#ifndef USE_MC_CORE
#define USE_MC_CORE 1
#endif

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_core/juce_core.h>
#include <juce_events/juce_events.h>

#include <mc_external/mc_external.hpp>

#include <algorithm>
#include <array>
#include <atomic>
#include <cstdint>
#include <mutex>
#include <thread>
#include <type_traits>

#include "system/platform.hpp"

#include "system/assert.hpp"
#include "system/crtp.hpp"

#include "text/format.hpp"
#include "text/string_utils.hpp"
#include "text/text_value_converter.hpp"

#include "container/registry.hpp"
#include "container/variant.hpp"
#include "container/vector.hpp"

#include "javascript/json_utils.hpp"
#include "math/constants.hpp"
#include "math/range_utils.hpp"
#include "thread/thread_safe_queue.hpp"
#include "time/time_utils.hpp"

#include "thread/background_process.hpp"
#include "thread/left_right.hpp"

#include "benchmark/profile.hpp"

#endif  // MODERN_CIRCUITS_JUCE_MODULES_MC_CORE_HPP
