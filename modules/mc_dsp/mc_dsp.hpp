/*
BEGIN_JUCE_MODULE_DECLARATION

    ID:                 mc_dsp
    vendor:             Modern Circuits
    version:            0.1.0
    name:               DSP
    description:        JUCE dsp extensions and utilities.
    dependencies:       juce_dsp, mc_audio_basics, mc_data_structures, mc_gui_basics
    website:            http://github.com/ModernCircuits/mc-juce
    license:            GPL/Commercial
    minimumCppStandard: 17

END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_MC_DSP
    #define USE_MC_DSP
#endif

#include <juce_dsp/juce_dsp.h>
#include <mc_audio_basics/mc_audio_basics.hpp>
#include <mc_data_structures/mc_data_structures.hpp>
#include <mc_gui_basics/mc_gui_basics.hpp>

#include "algorithm/averager.hpp"
#include "algorithm/down_sample.hpp"
#include "algorithm/frequency_for_bin.hpp"
#include "algorithm/rms_error.hpp"

#include "container/audio_block.hpp"
#include "container/ring_buffer.hpp"

#include "units/bars.hpp"
#include "units/bpm.hpp"
#include "units/sample_count.hpp"

#include "clock/trigger_clock.hpp"

#include "fx/airwindows_derez.hpp"
#include "fx/stereo_width.hpp"
