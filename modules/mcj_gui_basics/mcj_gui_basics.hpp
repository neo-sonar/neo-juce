/*
BEGIN_JUCE_MODULE_DECLARATION

    ID:                 mcj_gui_basics
    vendor:             Modern Circuits
    version:            0.1.0
    name:               GUI Basics
    description:        JUCE gui extensions and utilities.
    dependencies:       juce_gui_basics, mcj_data_structures, mcj_graphics
    website:            http://github.com/ModernCircuits/mc-juce
    license:            GPL/Commercial
    minimumCppStandard: 17

END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_MC_GUI_BASICS
    #define USE_MC_GUI_BASICS
#endif

#include <juce_gui_basics/juce_gui_basics.h>
#include <mcj_data_structures/mcj_data_structures.hpp>
#include <mcj_graphics/mcj_graphics.hpp>

#include "button/ButtonUtils.hpp"

#include "mouse/MouseUtils.hpp"

#include "widget/Components.hpp"
#include "widget/Placeholder.hpp"
#include "widget/Slider.hpp"
#include "widget/XYPad.hpp"

#include "attachment/LabelAttachment.hpp"
#include "attachment/SliderAttachment.hpp"
#include "attachment/ToggleButtonAttachment.hpp"
#include "attachment/TwoValueSliderAttachment.hpp"
