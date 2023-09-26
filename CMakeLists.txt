cmake_minimum_required(VERSION 3.23)
project(mc-juce-dev VERSION 0.1.0 LANGUAGES C CXX)

option(MC_BUILD_CONAN_CMAKE "Call conan from CMake. Does not work with ClangCL" ON)

find_program(CCACHE ccache)
if (CCACHE)
    set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE})
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE})
endif ()

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(FetchContent)
FetchContent_Declare(JUCE GIT_REPOSITORY "https://github.com/juce-framework/JUCE" GIT_TAG "develop")
FetchContent_MakeAvailable(JUCE)

juce_disable_default_flags()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_BINARY_DIR})
include(mcCompilerOptions)
include(mcCompilerWarnings)
include(mcCodeCoverage)

if(MC_BUILD_CONAN_CMAKE)
    include(mcConan)
endif()

find_package(Boost 1.78 REQUIRED COMPONENTS boost)
find_package(concurrentqueue REQUIRED)
find_package(fmt REQUIRED)

add_subdirectory(modules)

enable_testing()
include(CTest)

find_package(Catch2 REQUIRED)
include(Catch)

juce_add_console_app(mc_juce_tests PRODUCT_NAME "mc_juce_tests" NEEDS_CURL OFF)
catch_discover_tests(mc_juce_tests WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

set(test_sources
    modules/mc_audio_basics/buffers/audio_buffer.test.cpp

    modules/mc_audio_processors/attachment/xypad_attachment.test.cpp
    modules/mc_audio_processors/parameter/text_value_converter.test.cpp
    modules/mc_audio_processors/processors/buses_layout.test.cpp

    modules/mc_core/container/registry.test.cpp
    modules/mc_core/files/file.test.cpp
    # modules/mc_core/javascript/json_utils.test.cpp
    modules/mc_core/math/range.test.cpp
    modules/mc_core/misc/result.test.cpp
    modules/mc_core/text/jformat.test.cpp
    modules/mc_core/time/time.test.cpp

    modules/mc_dsp/algorithm/down_sample.test.cpp
    modules/mc_dsp/clock/trigger_clock.test.cpp
    modules/mc_dsp/container/audio_block.test.cpp
    modules/mc_dsp/fx/stereo_width.test.cpp
    modules/mc_dsp/units/units.test.cpp

    modules/mc_extension_pack/file/file_searcher.test.cpp
    modules/mc_extension_pack/pack/extension_pack_builder.test.cpp

    modules/mc_graphics/color/color.test.cpp
    modules/mc_graphics/geometry/geometry.test.cpp
    modules/mc_graphics/images/image.test.cpp

    modules/mc_gui_basics/attachment/attachment.test.cpp
    modules/mc_gui_basics/widgets/xy_pad.test.cpp

    modules/mc_meters/level_meter/level_meter_source.test.cpp

    modules/mc_synth/math/hermite_interpolation.test.cpp
    modules/mc_synth/wavetable/wavetable_oscillator.test.cpp
)

target_sources(mc_juce_tests PRIVATE main.test.cpp ${test_sources})
set_target_properties(mc_juce_tests PROPERTIES UNITY_BUILD_MODE GROUP)
set_source_files_properties(mc_juce_tests ${test_sources} PROPERTIES UNITY_GROUP "src")

target_compile_definitions(mc_juce_tests
    PRIVATE
        JUCE_WEB_BROWSER=0
        JUCE_USE_OGGVORBIS=0
        JUCE_USE_CURL=0
        JUCE_DISABLE_JUCE_VERSION_PRINTING=1
)

target_link_libraries(mc_juce_tests
    PRIVATE
        Boost::headers
        concurrentqueue::concurrentqueue
        fmt::fmt

        Catch2::Catch2

        mc::mc_audio_basics
        mc::mc_audio_formats
        mc::mc_audio_processors
        mc::mc_core
        mc::mc_data_structures
        mc::mc_dsp
        mc::mc_events
        mc::mc_extension_pack
        mc::mc_graphics
        mc::mc_gui_basics
        mc::mc_gui_extra
        mc::mc_meters
        mc::mc_synth

        juce::juce_recommended_warning_flags
        juce::juce_recommended_config_flags

        mc::compiler_options
        mc::coverage
)

message("------------------------------------------")
message("PROJECT:          \t ${PROJECT_NAME}")
message("VERSION:          \t ${PROJECT_VERSION}")
message("CC:               \t ${CMAKE_C_COMPILER}")
message("CXX:              \t ${CMAKE_CXX_COMPILER}")
message("COMPILER:         \t ${CMAKE_CXX_COMPILER_ID}")
message("GENERATOR:        \t ${CMAKE_GENERATOR}")
message("BUILD:            \t ${CMAKE_BUILD_TYPE}")
message("CCACHE:           \t ${CCACHE}")
message("C:                \t ${CMAKE_C_STANDARD}")
message("C++:              \t ${CMAKE_CXX_STANDARD}")
message("MACOS:            \t ${CMAKE_OSX_DEPLOYMENT_TARGET}")
message("------------------------------------------")
