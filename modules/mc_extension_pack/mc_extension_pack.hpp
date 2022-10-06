// SPDX-License-Identifier: BSL-1.0

/*
BEGIN_JUCE_MODULE_DECLARATION

    ID:                 mc_extension_pack
    vendor:             Modern Circuits
    version:            0.1.0
    name:               Modern Circuits Extension Packs
    dependencies:       mc_core
    website:            http://github.com/ModernCircuits/mc-juce
    license:            BSL-1.0
    minimumCppStandard: 17

END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_MC_EXTENSION_PACK
    #define USE_MC_EXTENSION_PACK
#endif

#include <mc_core/mc_core.hpp>

#include "file/file_searcher.hpp"
#include "file/has_magic_header.hpp"

#include "pack/asset_loader.hpp"
#include "pack/extension_pack_spec.hpp"

#include "pack/extension_pack_builder.hpp"
