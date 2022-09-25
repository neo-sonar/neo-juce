/*
 BEGIN_JUCE_MODULE_DECLARATION

 ID:            mc_dsp
 vendor:        mc
 version:       0.1.0
 name:          DSP
 description:   JUCE dsp extensions and utilities.
 dependencies:  juce_dsp, mc_audio_basics, mc_data_structures, mc_gui_basics

 END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_MC_DSP
    #define USE_MC_DSP
#endif

#include <mc/dsp.hpp>

#include <juce_dsp/juce_dsp.h>
#include <mc_audio_basics/mc_audio_basics.hpp>
#include <mc_data_structures/mc_data_structures.hpp>
#include <mc_gui_basics/mc_gui_basics.hpp>

#include "algorithm/downSample.hpp"

#include "container/RingBuffer.hpp"

#include "clock/Bars.hpp"
#include "clock/TriggerClock.hpp"

#include "fx/StereoWidth.hpp"

#include "analyzer/DownSamplingAnalyzer.hpp"
#include "analyzer/HistogramSource.hpp"
#include "analyzer/OscilloscopeSource.hpp"
#include "analyzer/SpectrumSource.hpp"

#include "analyzer/Histogram.hpp"
#include "analyzer/Oscilloscope.hpp"
#include "analyzer/Spectrum.hpp"
