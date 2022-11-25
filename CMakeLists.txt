cmake_minimum_required(VERSION 3.21)
project(mc-juce-dev VERSION 0.1.0)

option(MC_BUILD_CONAN_CMAKE "Call conan from CMake. Does not work with ClangCL" ON)

find_program(CCACHE ccache)
if (CCACHE)
    set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE})
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
include(mcCompilerOptions)
include(mcCompilerWarnings)
include(mcCodeCoverage)

if(MC_BUILD_CONAN_CMAKE)
    include(mcConan)
endif()

find_package(mc-core REQUIRED)
find_package(mc-audio REQUIRED)
find_package(EnTT REQUIRED)

add_subdirectory(modules)

enable_testing()
include(CTest)

find_package(Catch2 REQUIRED)
include(Catch)

juce_add_console_app(mc-juce-dev_tests PRODUCT_NAME "mc-juce-dev_tests" NEEDS_CURL TRUE)
catch_discover_tests(mc-juce-dev_tests WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
set_target_properties(mc-juce-dev_tests PROPERTIES UNITY_BUILD_MODE GROUP)

set(test_sources
    modules/mc_audio_basics/buffers/audio_buffer.test.cpp
    modules/mc_audio_basics/buffers/audio_buffers.test.cpp
    modules/mc_audio_basics/buffers/buffer_with_samplerate.test.cpp

    modules/mc_audio_processors/attachment/xypad_attachment.test.cpp
    modules/mc_audio_processors/parameter/audio_processor_value_tree_state.test.cpp
    modules/mc_audio_processors/processors/buses_layout.test.cpp
    modules/mc_audio_processors/text_value_converter/active_text_converter.test.cpp
    modules/mc_audio_processors/text_value_converter/frequency_text_converter.test.cpp
    modules/mc_audio_processors/text_value_converter/gain_text_converter.test.cpp
    modules/mc_audio_processors/text_value_converter/invert_phase_text_converter.test.cpp
    modules/mc_audio_processors/text_value_converter/milliseconds_text_converter.test.cpp
    modules/mc_audio_processors/text_value_converter/percent_text_converter.test.cpp
    modules/mc_audio_processors/text_value_converter/quality_text_converter.test.cpp
    modules/mc_audio_processors/text_value_converter/ratio_or_gate_text_converter.test.cpp
    modules/mc_audio_processors/text_value_converter/ratio_or_limiter_text_converter.test.cpp
    modules/mc_audio_processors/text_value_converter/seconds_text_converter.test.cpp
    modules/mc_audio_processors/text_value_converter/true_false_text_converter.test.cpp

    modules/mc_core/container/registry.test.cpp
    modules/mc_core/files/file.test.cpp
    modules/mc_core/files/zip_file.test.cpp
    # modules/mc_core/javascript/json_utils.test.cpp
    modules/mc_core/math/normalisable_range.test.cpp
    modules/mc_core/math/range.test.cpp
    modules/mc_core/math/default_range.test.cpp
    modules/mc_core/misc/result.test.cpp
    modules/mc_core/text/jformat.test.cpp
    modules/mc_core/time/duration.test.cpp
    modules/mc_core/time/time.test.cpp

    modules/mc_data_structures/values/atomic_wrapper.test.cpp
    modules/mc_data_structures/values/constrainer_wrapper.test.cpp

    modules/mc_dsp/algorithm/averager.test.cpp
    modules/mc_dsp/algorithm/down_sample.test.cpp
    modules/mc_dsp/clock/trigger_clock.test.cpp
    modules/mc_dsp/container/audio_block.test.cpp
    modules/mc_dsp/fx/airwindows_derez.test.cpp
    modules/mc_dsp/fx/stereo_width.test.cpp
    modules/mc_dsp/units/bars.test.cpp
    modules/mc_dsp/units/bpm.test.cpp
    modules/mc_dsp/units/sample_count.test.cpp

    modules/mc_extension_pack/file/file_searcher.test.cpp
    modules/mc_extension_pack/file/has_magic_header.test.cpp
    modules/mc_extension_pack/pack/asset_loader.test.cpp
    modules/mc_extension_pack/pack/extension_pack_builder.test.cpp

    modules/mc_graphics/color/color.test.cpp
    modules/mc_graphics/geometry/line.test.cpp
    modules/mc_graphics/geometry/point.test.cpp
    modules/mc_graphics/geometry/rectangle.test.cpp
    modules/mc_graphics/images/image.test.cpp

    modules/mc_gui_basics/attachment/label_attachment.test.cpp
    modules/mc_gui_basics/attachment/slider_attachment.test.cpp
    modules/mc_gui_basics/widgets/xy_pad.test.cpp

    modules/mc_lottie/model/lottie_model.test.cpp
    modules/mc_lottie/property/lottie_color.test.cpp
    modules/mc_lottie/shape/lottie_shape_ellipse.test.cpp
    modules/mc_lottie/shape/lottie_shape_fill.test.cpp
    modules/mc_lottie/shape/lottie_shape_gradient_fill.test.cpp
    modules/mc_lottie/shape/lottie_shape_gradient_stroke.test.cpp
    modules/mc_lottie/shape/lottie_shape_group.test.cpp
    modules/mc_lottie/shape/lottie_shape_path.test.cpp
    modules/mc_lottie/shape/lottie_shape_rectangle.test.cpp
    modules/mc_lottie/shape/lottie_shape_transform.test.cpp
    modules/mc_lottie/shape/lottie_shape_trim.test.cpp
    modules/mc_lottie/shape/lottie_shape.test.cpp

    modules/mc_meters/level_meter/level_meter_source.test.cpp

    modules/mc_synth/math/hermite_interpolation.test.cpp
    modules/mc_synth/wavetable/unison_oscillator.test.cpp
    modules/mc_synth/wavetable/wavetable_oscillator.test.cpp
    modules/mc_synth/wavetable/wavetable.test.cpp
)

target_sources(mc-juce-dev_tests PRIVATE main.test.cpp ${test_sources})
set_source_files_properties(mc-juce-dev_tests ${test_sources} PROPERTIES UNITY_GROUP "tests")

target_compile_definitions(mc-juce-dev_tests
    PRIVATE
        JUCE_WEB_BROWSER=0
        JUCE_USE_OGGVORBIS=0
        JUCE_DISABLE_JUCE_VERSION_PRINTING=1
        _SILENCE_CXX23_ALIGNED_STORAGE_DEPRECATION_WARNING=1
)

target_link_libraries(mc-juce-dev_tests
    PRIVATE
        mc-core::mc-core
        mc-audio::mc-audio

        EnTT::EnTT
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
        mc::mc_lottie
        mc::mc_meters

        mc::compiler_options
        mc::compiler_warnings
        mc::coverage

        juce::juce_recommended_warning_flags
        juce::juce_recommended_config_flags
)

find_package(benchmark)
juce_add_console_app(mc-juce-dev_benchmarks PRODUCT_NAME "mc-juce-dev_benchmarks")

set(bench_sources
    modules/mc_synth/math/hermite_interpolation.bench.cpp
    modules/mc_synth/wavetable/unison_oscillator.bench.cpp
    modules/mc_synth/wavetable/wavetable_oscillator.bench.cpp
)

target_sources(mc-juce-dev_benchmarks PRIVATE main.bench.cpp ${bench_sources})
set_target_properties(mc-juce-dev_benchmarks PROPERTIES UNITY_BUILD_MODE GROUP)
set_source_files_properties(mc-juce-dev_benchmarks ${bench_sources} PROPERTIES UNITY_GROUP "benchmarks")

target_compile_definitions(mc-juce-dev_benchmarks
    PRIVATE
        JUCE_WEB_BROWSER=0
        JUCE_USE_OGGVORBIS=0
        JUCE_DISABLE_JUCE_VERSION_PRINTING=1
        _SILENCE_CXX23_ALIGNED_STORAGE_DEPRECATION_WARNING=1
)

target_link_libraries(mc-juce-dev_benchmarks
    PRIVATE
        mc::mc_synth

        mc-core::mc-core
        mc-audio::mc-audio
        benchmark::benchmark

        mc::compiler_options
        mc::compiler_warnings
        mc::coverage

        juce::juce_recommended_warning_flags
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
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
