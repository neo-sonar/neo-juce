/*
BEGIN_JUCE_MODULE_DECLARATION

    ID:                 neo_graphics
    vendor:             neo-sonar
    version:            0.1.0
    name:               Graphics
    description:        JUCE graphics extensions and utilities.
    dependencies:       juce_graphics, neo_core
    website:            http://github.com/neo-sonar/neo-juce
    license:            GPL/Commercial
    minimumCppStandard: 20

END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_MC_GRAPHICS
    #define USE_MC_GRAPHICS
#endif

#include <juce_graphics/juce_graphics.h>
#include <neo_core/neo_core.hpp>

#include "color/color.hpp"
#include "geometry/line.hpp"
#include "geometry/point.hpp"
#include "geometry/rectangle.hpp"
#include "images/image.hpp"
#include "images/images.hpp"
