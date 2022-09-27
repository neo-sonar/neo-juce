cmake_minimum_required(VERSION 3.15)
cmake_policy(VERSION 3.15)
project(mc-juce-dev VERSION 0.1.0)

find_program(CCACHE ccache)
if (CCACHE)
    set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE})
endif ()

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

if(NOT "${CMAKE_CXX_STANDARD}")
    set(CMAKE_CXX_STANDARD 17)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(FetchContent)
FetchContent_Declare(JUCE GIT_REPOSITORY "https://github.com/juce-framework/JUCE" GIT_TAG "7.0.2")
FetchContent_MakeAvailable(JUCE)

juce_disable_default_flags()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_BINARY_DIR})
include(mcConan)
include(mcCompilerOptions)
include(mcCompilerWarnings)
include(mcCodeCoverage)

find_package(mc-core REQUIRED)
find_package(mc-dsp REQUIRED)

add_subdirectory(modules)

enable_testing()
include(CTest)

find_package(Catch2 REQUIRED)
include(Catch)

juce_add_console_app(${PROJECT_NAME}_tests PRODUCT_NAME "${PROJECT_NAME}_tests" NEEDS_CURL TRUE)
catch_discover_tests(${PROJECT_NAME}_tests)

target_sources(${PROJECT_NAME}_tests
    PRIVATE
        MainTest.cpp

        modules/mcj_audio_basics/buffers/audio_buffers.test.cpp

        modules/mcj_audio_processors/attachment/xypad_attachment.test.cpp
        modules/mcj_audio_processors/parameter/audio_processor_value_tree_state.test.cpp
        modules/mcj_audio_processors/processors/buses_layout.test.cpp
        modules/mcj_audio_processors/text_value_converter/active_text_converter.test.cpp
        modules/mcj_audio_processors/text_value_converter/frequency_text_converter.test.cpp
        modules/mcj_audio_processors/text_value_converter/gain_text_converter.test.cpp
        modules/mcj_audio_processors/text_value_converter/invert_phase_text_converter.test.cpp
        modules/mcj_audio_processors/text_value_converter/milliseconds_text_converter.test.cpp
        modules/mcj_audio_processors/text_value_converter/percent_text_converter.test.cpp
        modules/mcj_audio_processors/text_value_converter/quality_text_converter.test.cpp
        modules/mcj_audio_processors/text_value_converter/ratio_or_gate_text_converter.test.cpp
        modules/mcj_audio_processors/text_value_converter/ratio_or_limiter_text_converter.test.cpp
        modules/mcj_audio_processors/text_value_converter/seconds_text_converter.test.cpp
        modules/mcj_audio_processors/text_value_converter/true_false_text_converter.test.cpp

        modules/mcj_core/container/registry.test.cpp
        # modules/mcj_core/javascript/json_utils.test.cpp
        modules/mcj_core/math/normalisable_range.test.cpp
        modules/mcj_core/math/range.test.cpp
        modules/mcj_core/misc/result.test.cpp
        modules/mcj_core/text/jformat.test.cpp
        modules/mcj_core/time/duration.test.cpp
        modules/mcj_core/time/time.test.cpp

        modules/mcj_data_structures/values/atomic_wrapper.test.cpp
        modules/mcj_data_structures/values/constrainer_wrapper.test.cpp

        modules/mcj_dsp/algorithm/downSample.test.cpp
        modules/mcj_dsp/clock/TriggerClock.test.cpp
        modules/mcj_dsp/fx/StereoWidth.test.cpp

        modules/mcj_extension_pack/file/has_magic_header.test.cpp

        modules/mcj_graphics/color/color.test.cpp
        modules/mcj_graphics/geometry/line.test.cpp
        modules/mcj_graphics/geometry/point.test.cpp
        modules/mcj_graphics/geometry/rectangle.test.cpp
        modules/mcj_graphics/images/image.test.cpp

        modules/mcj_gui_basics/attachment/LabelAttachment.test.cpp
        modules/mcj_gui_basics/attachment/SliderAttachment.test.cpp

        modules/mcj_gui_basics/widget/XYPad.test.cpp
)

target_compile_definitions(${PROJECT_NAME}_tests
    PRIVATE
        JUCE_WEB_BROWSER=0
        JUCE_USE_OGGVORBIS=0
        JUCE_DISABLE_JUCE_VERSION_PRINTING=1
        _SILENCE_CXX23_ALIGNED_STORAGE_DEPRECATION_WARNING=1
)

target_link_libraries(${PROJECT_NAME}_tests
    PRIVATE
        Catch2::Catch2

        mc-core::mc-core
        mc-dsp::mc-dsp

        mc::mcj_audio_basics
        mc::mcj_audio_formats
        mc::mcj_audio_processors
        mc::mcj_core
        mc::mcj_data_structures
        mc::mcj_dsp
        mc::mcj_events
        mc::mcj_extension_pack
        mc::mcj_graphics
        mc::mcj_gui_basics
        mc::mcj_meters

        mc::compiler_options
        mc::compiler_warnings
        mc::coverage

        juce::juce_recommended_warning_flags
        juce::juce_recommended_config_flags
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
