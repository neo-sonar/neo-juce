/*
 BEGIN_JUCE_MODULE_DECLARATION

 ID:            mc_external
 vendor:        mc
 version:       0.1.0
 name:          3rd party code
 description:   Modern Circuits 3rd party header only libraries
 searchpaths:   3rd_party/GSL/include, 3rd_party/fmt/include

 END_JUCE_MODULE_DECLARATION
 */

#ifndef MODERN_CIRCUITS_JUCE_MODULES_MC_EXTERNAL_HPP
#define MODERN_CIRCUITS_JUCE_MODULES_MC_EXTERNAL_HPP

#ifndef USE_MC_EXTERNAL
#define USE_MC_EXTERNAL 1
#endif

#define FMT_HEADER_ONLY 1
#include "fmt/chrono.h"
#include "fmt/format.h"
#include "fmt/ostream.h"

#include <gsl/gsl>

#include <boost/optional.hpp>

#endif  // MODERN_CIRCUITS_JUCE_MODULES_MC_EXTERNAL_HPP
