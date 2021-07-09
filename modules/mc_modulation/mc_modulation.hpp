/*
 BEGIN_JUCE_MODULE_DECLARATION

 ID:            mc_modulation
 vendor:        mc
 version:       0.1.0
 name:          Modulation
 description:   Audio modulators, routing matrix & utilities.
 dependencies:  juce_audio_basics, mc_data_structures, mc_graphics

 END_JUCE_MODULE_DECLARATION
 */

#ifndef MODERN_CIRCUITS_JUCE_MODULES_MC_MODULATION_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_MC_MODULATION_HPP

#ifndef USE_MC_MODULATION
#define USE_MC_MODULATION 1
#endif

#include <juce_audio_basics/juce_audio_basics.h>
#include <mc_data_structures/mc_data_structures.hpp>
#include <mc_graphics/mc_graphics.hpp>

// clang-format off
#include "core/mc_Modulator.hpp"
#include "core/mc_ModulatorList.hpp"
#include "core/mc_ModulationMatrix.hpp"

#include "modulator/mc_ModulatorMacro.hpp"

// clang-format on

#endif  // MODERN_CIRCUITS_JUCE_MODULES_MC_MODULATION_HPP
