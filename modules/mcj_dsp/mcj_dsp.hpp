/*
BEGIN_JUCE_MODULE_DECLARATION

    ID:                 mcj_dsp
    vendor:             Modern Circuits
    version:            0.1.0
    name:               DSP
    description:        JUCE dsp extensions and utilities.
    dependencies:       juce_dsp, mcj_audio_basics, mcj_data_structures, mcj_gui_basics
    website:            http://github.com/ModernCircuits/mc-juce
    license:            GPL/Commercial
    minimumCppStandard: 17

END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_MCJ_DSP
    #define USE_MCJ_DSP
#endif

#include <juce_dsp/juce_dsp.h>
#include <mcj_audio_basics/mcj_audio_basics.hpp>
#include <mcj_data_structures/mcj_data_structures.hpp>
#include <mcj_gui_basics/mcj_gui_basics.hpp>

#include "algorithm/averager.hpp"
#include "algorithm/downSample.hpp"
#include "algorithm/frequency_for_bin.hpp"
#include "algorithm/rms_error.hpp"

#include "container/RingBuffer.hpp"
#include "container/audio_block.hpp"

#include "clock/Bars.hpp"
#include "clock/TriggerClock.hpp"

#include "fx/StereoWidth.hpp"
