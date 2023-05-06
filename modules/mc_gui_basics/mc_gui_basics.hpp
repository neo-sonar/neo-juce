/*
BEGIN_JUCE_MODULE_DECLARATION

    ID:                 mc_gui_basics
    vendor:             Modern Circuits
    version:            0.1.0
    name:               GUI Basics
    description:        JUCE gui extensions and utilities.
    dependencies:       juce_gui_basics, mc_data_structures, mc_graphics
    website:            http://github.com/ModernCircuits/mc-juce
    license:            GPL/Commercial
    minimumCppStandard: 20

END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_MC_GUI_BASICS
    #define USE_MC_GUI_BASICS
#endif

#include <juce_gui_basics/juce_gui_basics.h>
#include <mc_data_structures/mc_data_structures.hpp>
#include <mc_graphics/mc_graphics.hpp>

#include "mouse/mouse_event.hpp"

#include "widgets/placeholder.hpp"
#include "widgets/slider_listener.hpp"
#include "widgets/xy_pad.hpp"

#include "attachment/label_attachment.hpp"
#include "attachment/slider_attachment.hpp"
#include "attachment/toggle_button_attachment.hpp"
#include "attachment/two_value_slider_attachment.hpp"
