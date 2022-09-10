/*
 BEGIN_JUCE_MODULE_DECLARATION

 ID:            mc_core
 vendor:        mc
 version:       0.1.0
 name:          Modern Circuits JUCE Core module
 description:   Core JUCE extensions and utilities.
 dependencies:  juce_core

 END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_MC_CORE
    #define USE_MC_CORE
#endif

#include <juce_core/juce_core.h>

#include <mc/core.hpp>

#include "text/Format.hpp"
#include "text/String.hpp"
#include "text/Strings.hpp"

#include "container/Array.hpp"
#include "container/BitSet.hpp"
#include "container/Registry.hpp"
#include "container/Span.hpp"
#include "container/StringArray.hpp"
#include "files/File.hpp"
#include "files/ZipFile.hpp"
#include "javascript/JSONUtils.hpp"
#include "math/NormalisableRange.hpp"
#include "math/Range.hpp"
#include "math/RangeUtils.hpp"
#include "misc/Result.hpp"
#include "time/Duration.hpp"
#include "time/Time.hpp"

#include "benchmark/Profile.hpp"
