/*
 BEGIN_JUCE_MODULE_DECLARATION

 ID:            mcj_graphics
 vendor:        mc
 version:       0.1.0
 name:          Graphics
 description:   JUCE graphics extensions and utilities.
 dependencies:  juce_graphics, mcj_core

 END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_MC_GRAPHICS
    #define USE_MC_GRAPHICS
#endif

#include <juce_graphics/juce_graphics.h>
#include <mcj_core/mcj_core.hpp>

#include "color/Color.hpp"
#include "geometry/Line.hpp"
#include "geometry/Point.hpp"
#include "geometry/Rectangle.hpp"
#include "images/Image.hpp"
#include "images/ImageUtils.hpp"
