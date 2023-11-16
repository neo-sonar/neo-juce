// SPDX-License-Identifier: BSL-1.0

/*
BEGIN_JUCE_MODULE_DECLARATION

    ID:                 neo_extension_pack
    vendor:             neo-sonar
    version:            0.1.0
    name:               neo-sonar Extension Packs
    dependencies:       neo_core
    website:            http://github.com/neo-sonar/neo-juce
    license:            BSL-1.0
    minimumCppStandard: 20

END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_MC_EXTENSION_PACK
    #define USE_MC_EXTENSION_PACK
#endif

#include <neo_core/neo_core.hpp>

#include "file/file_searcher.hpp"
#include "file/has_magic_header.hpp"

#include "pack/asset_loader.hpp"
#include "pack/extension_pack_spec.hpp"

#include "pack/extension_pack_builder.hpp"
