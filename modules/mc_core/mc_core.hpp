// SPDX-License-Identifier: BSL-1.0

/*
BEGIN_JUCE_MODULE_DECLARATION

    ID:                 mc_core
    vendor:             Modern Circuits
    version:            0.1.0
    name:               Modern Circuits JUCE Core module
    description:        Core JUCE extensions and utilities.
    dependencies:       juce_core
    website:            http://github.com/ModernCircuits/mc-juce
    license:            BSL-1.0
    minimumCppStandard: 20

END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_MC_CORE
    #define USE_MC_CORE
#endif

#include <juce_core/juce_core.h>

#include <mc/core.hpp>

#include "text/jformat.hpp"
#include "text/string.hpp"
#include "text/strings.hpp"

#include "container/array.hpp"
#include "container/bitset.hpp"
#include "container/registry.hpp"
#include "container/span.hpp"
#include "container/string_array.hpp"
#include "files/file.hpp"
#include "files/zip_file.hpp"
#include "javascript/json_utils.hpp"
#include "math/normalisable_range.hpp"
#include "math/range.hpp"
#include "memory/memory_block.hpp"
#include "misc/result.hpp"
#include "time/duration.hpp"
#include "time/time.hpp"
