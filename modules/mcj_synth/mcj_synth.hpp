/*
BEGIN_JUCE_MODULE_DECLARATION

    ID:                 mcj_synth
    vendor:             Modern Circuits
    version:            0.1.0
    name:               Modern Circuits Extension Packs
    dependencies:       mcj_audio_formats, mcj_dsp
    website:            http://github.com/ModernCircuits/mc-juce
    license:            GPL/Commercial
    minimumCppStandard: 17

END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_MCJ_EXTENSION_PACK
    #define USE_MCJ_EXTENSION_PACK
#endif

#include <mcj_audio_formats/mcj_audio_formats.hpp>
#include <mcj_dsp/mcj_dsp.hpp>

#include "math/hermite_interpolation.hpp"
#include "wavetable/wavetable.hpp"
#include "wavetable/wavetable_oscillator.hpp"
