/*
BEGIN_JUCE_MODULE_DECLARATION

    ID:                 neo_data_structures
    vendor:             neo-sonar
    version:            0.1.0
    name:               Data Structures
    description:        JUCE data structure extensions and utilities.
    dependencies:       juce_data_structures, neo_core
    website:            http://github.com/neo-sonar/neo-juce
    license:            GPL/Commercial
    minimumCppStandard: 20

END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_MC_DATA_STRUCTURES
    #define USE_MC_DATA_STRUCTURES
#endif

#include <juce_data_structures/juce_data_structures.h>

#include <neo_core/neo_core.hpp>

#include "values/atomic_wrapper.hpp"
#include "values/value_tree.hpp"
#include "values/value_tree_attachment.hpp"
#include "values/value_tree_object.hpp"
#include "values/value_tree_object_list.hpp"
