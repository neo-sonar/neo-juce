/*
 BEGIN_JUCE_MODULE_DECLARATION

 ID:            mc_graphics
 vendor:        mc
 version:       0.1.0
 name:          Graphics
 description:   JUCE graphics extensions and utilities.
 dependencies:  juce_graphics, mc_core

 END_JUCE_MODULE_DECLARATION
 */

#ifndef MODERN_CIRCUITS_JUCE_MODULES_MC_GRAPHICS_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_MC_GRAPHICS_HPP

#ifndef USE_MC_GRAPHICS
#define USE_MC_GRAPHICS 1
#endif

#include <juce_graphics/juce_graphics.h>
#include <mc_core/mc_core.hpp>

#include "color/color_utils.hpp"
#include "geometry/geometry_utils.hpp"
#include "images/image_utils.hpp"

#endif  // MODERN_CIRCUITS_JUCE_MODULES_MC_GRAPHICS_HPP
