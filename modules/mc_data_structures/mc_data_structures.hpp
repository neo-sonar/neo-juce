/*
BEGIN_JUCE_MODULE_DECLARATION

    ID:                 mc_data_structures
    vendor:             Modern Circuits
    version:            0.1.0
    name:               Data Structures
    description:        JUCE data structure extensions and utilities.
    dependencies:       juce_data_structures, mc_core
    website:            http://github.com/ModernCircuits/mc-juce
    license:            GPL/Commercial
    minimumCppStandard: 17

END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_MC_DATA_STRUCTURES
    #define USE_MC_DATA_STRUCTURES
#endif

#include <juce_data_structures/juce_data_structures.h>

#include <mc_core/mc_core.hpp>

#include "values/atomic_wrapper.hpp"
#include "values/constrainer_wrapper.hpp"
#include "values/value_tree.hpp"
#include "values/value_tree_attachment.hpp"
#include "values/value_tree_object.hpp"
#include "values/value_tree_object_list.hpp"
