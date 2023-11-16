/*
BEGIN_JUCE_MODULE_DECLARATION

    ID:                 neo_synth
    vendor:             neo-sonar
    version:            0.1.0
    name:               neo-sonar Extension Packs
    dependencies:       neo_audio_formats, neo_dsp
    website:            http://github.com/neo-sonar/neo-juce
    license:            GPL/Commercial
    minimumCppStandard: 20

END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_MC_SYNTH
    #define USE_MC_SYNTH
#endif

#include <neo_audio_formats/neo_audio_formats.hpp>
#include <neo_dsp/neo_dsp.hpp>

// clang-format off
#include "math/frequency.hpp"
#include "math/hermite_interpolation.hpp"
#include "wavetable/wavetable.hpp"
#include "wavetable/wavetable_oscillator.hpp"
#include "wavetable/unison_oscillator.hpp"
// clang-format on
