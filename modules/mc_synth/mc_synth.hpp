/*
BEGIN_JUCE_MODULE_DECLARATION

    ID:                 mc_synth
    vendor:             Modern Circuits
    version:            0.1.0
    name:               Modern Circuits Extension Packs
    dependencies:       mc_audio_formats, mc_dsp
    website:            http://github.com/ModernCircuits/mc-juce
    license:            GPL/Commercial
    minimumCppStandard: 17

END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_MC_SYNTH
    #define USE_MC_SYNTH
#endif

#include <mc_audio_formats/mc_audio_formats.hpp>
#include <mc_dsp/mc_dsp.hpp>

// clang-format off
#include "math/frequency.hpp"
#include "math/hermite_interpolation.hpp"
#include "wavetable/wavetable.hpp"
#include "wavetable/wavetable_oscillator.hpp"
#include "wavetable/unison_oscillator.hpp"
// clang-format on
