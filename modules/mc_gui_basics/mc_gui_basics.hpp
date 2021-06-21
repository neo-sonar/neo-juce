/*
 BEGIN_JUCE_MODULE_DECLARATION

 ID:            mc_gui_basics
 vendor:        mc
 version:       0.1.0
 name:          Graphics
 description:   JUCE graphics extensions and utilities.
 dependencies:  juce_gui_basics, mc_data_structures

 END_JUCE_MODULE_DECLARATION
 */

#ifndef MODERN_CIRCUITS_JUCE_MODULES_MC_GUI_BASICS_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_MC_GUI_BASICS_HPP

#ifndef USE_MC_GUI_BASICS
#define USE_MC_GUI_BASICS 1
#endif

#include <juce_gui_basics/juce_gui_basics.h>
#include <mc_data_structures/mc_data_structures.hpp>

#include "button/mc_ButtonUtils.hpp"

#include "mouse/mc_MouseUtils.hpp"

#include "widget/mc_BipolarFilter.hpp"
#include "widget/mc_TextBoxSlider.hpp"
#include "widget/mc_XYPad.hpp"

#include "attachment/mc_BipolarFilterAttachment.hpp"
#include "attachment/mc_LabelAttachment.hpp"
#include "attachment/mc_SliderAttachment.hpp"
#include "attachment/mc_TextBoxSliderAttachment.hpp"

#endif  // MODERN_CIRCUITS_JUCE_MODULES_MC_GUI_BASICS_HPP
