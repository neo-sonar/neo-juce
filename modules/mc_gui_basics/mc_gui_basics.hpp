/*
 BEGIN_JUCE_MODULE_DECLARATION

 ID:            mc_gui_basics
 vendor:        mc
 version:       0.1.0
 name:          Graphics
 description:   JUCE graphics extensions and utilities.
 dependencies:  juce_gui_basics, mc_data_structures, mc_graphics

 END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_MC_GUI_BASICS
    #define USE_MC_GUI_BASICS
#endif

#include <juce_gui_basics/juce_gui_basics.h>
#include <mc_data_structures/mc_data_structures.hpp>
#include <mc_graphics/mc_graphics.hpp>

#include "button/ButtonUtils.hpp"

#include "mouse/MouseUtils.hpp"

#include "widget/Components.hpp"
#include "widget/XYPad.hpp"

#include "attachment/LabelAttachment.hpp"
#include "attachment/SliderAttachment.hpp"
// #include "attachment/XYPadAttachment.hpp"
