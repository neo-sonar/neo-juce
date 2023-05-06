// SPDX-License-Identifier: BSL-1.0

/*
BEGIN_JUCE_MODULE_DECLARATION

    ID:                 mc_audio_basics
    vendor:             Modern Circuits
    version:            0.1.0
    name:               Modern Circuits JUCE Audio basics module
    description:        Audio basics JUCE extensions and utilities.
    dependencies:       juce_audio_basics, mc_core
    website:            http://github.com/ModernCircuits/mc-juce
    license:            BSL-1.0
    minimumCppStandard: 20

END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_MC_AUDIO_BASICS
    #define USE_MC_AUDIO_BASICS
#endif

#include <mc/audio.hpp>

#include <juce_audio_basics/juce_audio_basics.h>
#include <mc_core/mc_core.hpp>

#include "buffers/audio_buffer.hpp"
#include "buffers/audio_buffers.hpp"
#include "buffers/buffer_with_samplerate.hpp"
