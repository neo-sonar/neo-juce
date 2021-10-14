/*
 BEGIN_JUCE_MODULE_DECLARATION

 ID:            mc_dsp
 vendor:        mc
 version:       0.1.0
 name:          DSP
 description:   JUCE dsp extensions and utilities.
 dependencies:  juce_audio_processors, juce_dsp, mc_data_structures, mc_gui_basics

 END_JUCE_MODULE_DECLARATION
 */

#ifndef MODERN_CIRCUITS_JUCE_MODULES_MC_DSP_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_MC_DSP_HPP

#ifndef USE_MC_DSP
    #define USE_MC_DSP 1
#endif

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_dsp/juce_dsp.h>
#include <mc_data_structures/mc_data_structures.hpp>
#include <mc_gui_basics/mc_gui_basics.hpp>

#include "container/mc_AudioBufferPool.hpp"
#include "container/mc_AudioBufferQueue.hpp"
#include "container/mc_AudioBufferUtils.hpp"

#include "clock/Bars.hpp"
#include "clock/TriggerClock.hpp"

#include "util/mc_BusesLayoutUtils.hpp"

#include "processor/mc_MultiMonoIIR.hpp"
#include "processor/mc_StereoWidth.hpp"

#include "analyzer/mc_OscilloscopeSource.hpp"
#include "analyzer/mc_SpectrumSource.hpp"

#include "analyzer/mc_Oscilloscope.hpp"
#include "analyzer/mc_Spectrum.hpp"

// #include "airwindows/mc_AirWindowsCoils2.hpp"
//#include "airwindows/mc_AirWindowsVerbity.hpp"

#include "attachment/mc_XYPadAttachment.hpp"

#endif // MODERN_CIRCUITS_JUCE_MODULES_MC_DSP_HPP
