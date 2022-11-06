/*
BEGIN_JUCE_MODULE_DECLARATION

    ID:                 mc_lottie
    vendor:             Modern Circuits
    version:            0.1.0
    name:               Modern Circuits Lottie
    dependencies:       mc_core, mc_graphics
    website:            http://github.com/ModernCircuits/mc-juce
    license:            GPL/Commercial
    minimumCppStandard: 17

END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_MC_LOTTIE
    #define USE_MC_LOTTIE
#endif

#include <mc_core/mc_core.hpp>
#include <mc_graphics/mc_graphics.hpp>

// clang-format off
#include "detail/lottie_json_parser.hpp"
#include "types/lottie_blend_mode.hpp"
#include "layer/lottie_layer_type.hpp"
#include "layer/lottie_layer_null.hpp"
#include "layer/lottie_layer_shape.hpp"
#include "layer/lottie_layer.hpp"
#include "animation/lottie_animation.hpp"
// clang-format on
