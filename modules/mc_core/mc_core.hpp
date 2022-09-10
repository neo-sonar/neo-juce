/*
 BEGIN_JUCE_MODULE_DECLARATION

 ID:            mc_core
 vendor:        mc
 version:       0.1.0
 name:          Modern Circuits JUCE Core module
 description:   Core JUCE extensions and utilities.
 dependencies:  juce_core, juce_events, juce_audio_basics

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

#include <mc/core/algorithm.hpp>
#include <mc/core/array.hpp>
#include <mc/core/atomic.hpp>
#include <mc/core/bit.hpp>
#include <mc/core/cassert.hpp>
#include <mc/core/cctype.hpp>
#include <mc/core/cfloat.hpp>
#include <mc/core/chrono.hpp>
#include <mc/core/climits.hpp>
#include <mc/core/cmath.hpp>
#include <mc/core/complex.hpp>
#include <mc/core/config.hpp>
#include <mc/core/cstddef.hpp>
#include <mc/core/cstdint.hpp>
#include <mc/core/cstdlib.hpp>
#include <mc/core/cstring.hpp>
#include <mc/core/filesystem.hpp>
#include <mc/core/format.hpp>
#include <mc/core/fstream.hpp>
#include <mc/core/functional.hpp>
#include <mc/core/future.hpp>
#include <mc/core/initializer_list.hpp>
#include <mc/core/iomanip.hpp>
#include <mc/core/iterator.hpp>
#include <mc/core/limits.hpp>
#include <mc/core/map.hpp>
#include <mc/core/memory.hpp>
#include <mc/core/memory_resource.hpp>
#include <mc/core/mutex.hpp>
#include <mc/core/numbers.hpp>
#include <mc/core/numeric.hpp>
#include <mc/core/optional.hpp>
#include <mc/core/queue.hpp>
#include <mc/core/random.hpp>
#include <mc/core/set.hpp>
#include <mc/core/span.hpp>
#include <mc/core/sstream.hpp>
#include <mc/core/string.hpp>
#include <mc/core/string_view.hpp>
#include <mc/core/thread.hpp>
#include <mc/core/tuple.hpp>
#include <mc/core/type_traits.hpp>
#include <mc/core/units.hpp>
#include <mc/core/unordered_map.hpp>
#include <mc/core/utility.hpp>
#include <mc/core/variant.hpp>
#include <mc/core/vector.hpp>
#include <mc/core/version.hpp>

#include "text/Format.hpp"
#include "text/StringUtils.hpp"
#include "text/TextValueConverters.hpp"
#include "text/TrueFalseTextConverter.hpp"

#include "container/Registry.hpp"

#include "javascript/JSONUtils.hpp"
#include "math/RangeUtils.hpp"
#include "time/Duration.hpp"
#include "time/TimeUtils.hpp"

#include "thread/BackgroundProcess.hpp"

#include "benchmark/Profile.hpp"

#endif // MODERN_CIRCUITS_JUCE_MODULES_MC_CORE_HPP
