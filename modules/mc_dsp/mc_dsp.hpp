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

#include <mc/dsp.hpp>

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_dsp/juce_dsp.h>
#include <mc_data_structures/mc_data_structures.hpp>
#include <mc_gui_basics/mc_gui_basics.hpp>

#include "algorithm/downSample.hpp"

#include "container/AudioBufferPool.hpp"
#include "container/AudioBufferQueue.hpp"
#include "container/AudioBufferUtils.hpp"
#include "container/RingBuffer.hpp"

#include "clock/Bars.hpp"
#include "clock/TriggerClock.hpp"

#include "util/BusesLayoutUtils.hpp"

#include "processor/MultiMonoIIR.hpp"
#include "processor/StereoWidth.hpp"

#include "analyzer/DownSamplingAnalyzer.hpp"
#include "analyzer/HistogramSource.hpp"
#include "analyzer/OscilloscopeSource.hpp"
#include "analyzer/SpectrumSource.hpp"

#include "analyzer/Histogram.hpp"
#include "analyzer/Oscilloscope.hpp"
#include "analyzer/Spectrum.hpp"

// #include "airwindows/AirWindowsCoils2.hpp"
//#include "airwindows/AirWindowsVerbity.hpp"

#include "attachment/XYPadAttachment.hpp"

#endif // MODERN_CIRCUITS_JUCE_MODULES_MC_DSP_HPP
