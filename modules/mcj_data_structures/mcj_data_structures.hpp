/*
 BEGIN_JUCE_MODULE_DECLARATION

 ID:            mcj_data_structures
 vendor:        mc
 version:       0.1.0
 name:          Data Structures
 description:   JUCE data structure extensions and utilities.
 dependencies:  juce_data_structures, mcj_core

 END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_MC_DATA_STRUCTURES
    #define USE_MC_DATA_STRUCTURES
#endif

#include <juce_data_structures/juce_data_structures.h>

#include <mcj_core/mcj_core.hpp>

#include "value_tree/AtomicWrapper.hpp"
#include "value_tree/Attachment.hpp"
#include "value_tree/ConstrainerWrapper.hpp"
#include "value_tree/ObjectList.hpp"
