cmake_minimum_required(VERSION 3.23)
project(neo-juce-dev VERSION 0.1.0 LANGUAGES C CXX)

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

find_package(Boost 1.78 REQUIRED COMPONENTS boost)
find_package(concurrentqueue REQUIRED)
find_package(fmt REQUIRED)

add_subdirectory(modules)

enable_testing()
find_package(Catch2 REQUIRED)
include(Catch)

juce_add_console_app(neo_juce_tests PRODUCT_NAME "neo_juce_tests" NEEDS_CURL OFF)
catch_discover_tests(neo_juce_tests WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

set(test_sources
    modules/neo_audio_basics/buffers/audio_buffer_test.cpp

    modules/neo_audio_processors/attachment/xypad_attachment_test.cpp
    modules/neo_audio_processors/parameter/text_value_converter_test.cpp
    modules/neo_audio_processors/processors/buses_layout_test.cpp

    modules/neo_core/container/registry_test.cpp
    modules/neo_core/files/file_test.cpp
    # modules/neo_core/javascript/json_utils_test.cpp
    modules/neo_core/math/range_test.cpp
    modules/neo_core/misc/result_test.cpp
    modules/neo_core/text/jformat_test.cpp
    modules/neo_core/time/time_test.cpp

    modules/neo_dsp/algorithm/down_sample_test.cpp
    modules/neo_dsp/clock/trigger_clock_test.cpp
    modules/neo_dsp/container/audio_block_test.cpp
    modules/neo_dsp/fx/stereo_width_test.cpp
    modules/neo_dsp/units/units_test.cpp

    modules/neo_extension_pack/file/file_searcher_test.cpp
    modules/neo_extension_pack/pack/extension_pack_builder_test.cpp

    modules/neo_graphics/color/color_test.cpp
    modules/neo_graphics/geometry/geometry_test.cpp
    modules/neo_graphics/images/image_test.cpp

    modules/neo_gui_basics/attachment/attachment_test.cpp
    modules/neo_gui_basics/widgets/xy_pad_test.cpp

    modules/neo_meters/analyzer/spectrum_source_test.cpp
    modules/neo_meters/level_meter/level_meter_source_test.cpp
    modules/neo_meters/waveform/waveform_source_test.cpp

    modules/neo_synth/math/hermite_interpolation_test.cpp
    modules/neo_synth/wavetable/wavetable_oscillator_test.cpp
)

target_sources(neo_juce_tests PRIVATE main.cpp ${test_sources})
set_target_properties(neo_juce_tests PROPERTIES UNITY_BUILD_MODE GROUP)
set_source_files_properties(neo_juce_tests ${test_sources} PROPERTIES UNITY_GROUP "src")

target_compile_definitions(neo_juce_tests
    PRIVATE
        JUCE_WEB_BROWSER=0
        JUCE_USE_OGGVORBIS=0
        JUCE_USE_CURL=0
        JUCE_DISABLE_JUCE_VERSION_PRINTING=1
)

target_link_libraries(neo_juce_tests
    PRIVATE
        Boost::headers
        concurrentqueue::concurrentqueue
        fmt::fmt

        Catch2::Catch2

        neo::neo_audio_basics
        neo::neo_audio_formats
        neo::neo_audio_processors
        neo::neo_core
        neo::neo_data_structures
        neo::neo_dsp
        neo::neo_events
        neo::neo_extension_pack
        neo::neo_graphics
        neo::neo_gui_basics
        neo::neo_gui_extra
        neo::neo_meters
        neo::neo_synth

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
