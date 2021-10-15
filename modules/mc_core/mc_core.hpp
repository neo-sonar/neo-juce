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

#include "mc/algorithm.hpp"
#include "mc/array.hpp"
#include "mc/atomic.hpp"
#include "mc/bit.hpp"
#include "mc/cassert.hpp"
#include "mc/cctype.hpp"
#include "mc/cfloat.hpp"
#include "mc/chrono.hpp"
#include "mc/climits.hpp"
#include "mc/cmath.hpp"
#include "mc/complex.hpp"
#include "mc/cstddef.hpp"
#include "mc/cstdint.hpp"
#include "mc/cstdlib.hpp"
#include "mc/cstring.hpp"
#include "mc/filesystem.hpp"
#include "mc/format.hpp"
#include "mc/fstream.hpp"
#include "mc/functional.hpp"
#include "mc/future.hpp"
#include "mc/initializer_list.hpp"
#include "mc/iomanip.hpp"
#include "mc/iterator.hpp"
#include "mc/limits.hpp"
#include "mc/map.hpp"
#include "mc/memory.hpp"
#include "mc/memory_resource.hpp"
#include "mc/mutex.hpp"
#include "mc/numbers.hpp"
#include "mc/numeric.hpp"
#include "mc/optional.hpp"
#include "mc/preprocessor.hpp"
#include "mc/queue.hpp"
#include "mc/random.hpp"
#include "mc/set.hpp"
#include "mc/span.hpp"
#include "mc/sstream.hpp"
#include "mc/string.hpp"
#include "mc/string_view.hpp"
#include "mc/thread.hpp"
#include "mc/tuple.hpp"
#include "mc/type_traits.hpp"
#include "mc/units.hpp"
#include "mc/unordered_map.hpp"
#include "mc/utility.hpp"
#include "mc/variant.hpp"
#include "mc/vector.hpp"
#include "mc/version.hpp"

#include "text/Format.hpp"
#include "text/StringUtils.hpp"
#include "text/TextValueConverters.hpp"

#include "container/Registry.hpp"

#include "javascript/JSONUtils.hpp"
#include "math/RangeUtils.hpp"
#include "time/Duration.hpp"
#include "time/TimeUtils.hpp"

#include "thread/BackgroundProcess.hpp"

#include "benchmark/Profile.hpp"

#endif // MODERN_CIRCUITS_JUCE_MODULES_MC_CORE_HPP
