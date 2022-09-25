/*
BEGIN_JUCE_MODULE_DECLARATION

    ID:                 mcj_graphics
    vendor:             Modern Circuits
    version:            0.1.0
    name:               Graphics
    description:        JUCE graphics extensions and utilities.
    dependencies:       juce_graphics, mcj_core
    website:            http://github.com/ModernCircuits/mc-juce
    license:            GPL/Commercial
    minimumCppStandard: 17

END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_MCJ_GRAPHICS
    #define USE_MCJ_GRAPHICS
#endif

#include <juce_graphics/juce_graphics.h>
#include <mcj_core/mcj_core.hpp>

#include "color/color.hpp"
#include "geometry/line.hpp"
#include "geometry/point.hpp"
#include "geometry/rectangle.hpp"
#include "images/image.hpp"
#include "images/images.hpp"
