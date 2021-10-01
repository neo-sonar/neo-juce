cmake_minimum_required(VERSION 3.15)
cmake_policy(VERSION 3.15)

project(modern-circuits-juce-modules VERSION 0.1.0)

option(MC_BUILD_CONAN      "Build with dependencies build from conan"          ON)
option(MC_BUILD_COVERAGE   "Build with coverage enabled"                       OFF)
option(MC_BUILD_ASAN       "Build with address sanitizer enabled"              OFF)
option(MC_BUILD_UBSAN      "Build with undefined behavior sanitizer enabled"   OFF)
option(MC_BUILD_TSAN       "Build with thread sanitizer enabled"               OFF)
option(MC_BUILD_MSAN       "Build with memory sanitizer enabled"               OFF)
option(MC_BUILD_WERROR     "Build with warnings as errors"                     OFF)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(CMAKE_C_STANDARD 11)
    set(CMAKE_C_STANDARD_REQUIRED ON)
    set(CMAKE_C_EXTENSIONS OFF)

    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)

    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.12")
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
    set(CMAKE_CXX_VISIBILITY_PRESET hidden)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
    set(BUILD_SHARED_LIBS OFF)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    find_program(CCACHE ccache)
    if (CCACHE)
        set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE})
    endif ()
endif ()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(mcCompilerOptions)
include(mcCompilerWarnings)
include(mcCodeCoverage)

if(MC_BUILD_CONAN)
    list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_BINARY_DIR})
    list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_BINARY_DIR})
    include(mcConan)
endif()

find_package(Boost 1.77 REQUIRED)
find_package(fmt REQUIRED)
find_package(Microsoft.GSL REQUIRED)
find_package(concurrentqueue REQUIRED)
find_package(readerwriterqueue REQUIRED)

add_library(mc_external INTERFACE)
add_library(mc::mc_external ALIAS mc_external)
target_link_libraries(mc_external INTERFACE Boost::headers)
target_link_libraries(mc_external INTERFACE fmt::fmt)
target_link_libraries(mc_external INTERFACE Microsoft.GSL::Microsoft.GSL)
target_link_libraries(mc_external INTERFACE concurrentqueue::concurrentqueue)
target_link_libraries(mc_external INTERFACE readerwriterqueue::readerwriterqueue)

add_subdirectory(3rd_party/JUCE EXCLUDE_FROM_ALL)
juce_add_module(modules/mc_core             ALIAS_NAMESPACE mc)
juce_add_module(modules/mc_data_structures  ALIAS_NAMESPACE mc)
juce_add_module(modules/mc_dsp              ALIAS_NAMESPACE mc)
juce_add_module(modules/mc_graphics         ALIAS_NAMESPACE mc)
juce_add_module(modules/mc_gui_basics       ALIAS_NAMESPACE mc)
juce_add_module(modules/mc_meters           ALIAS_NAMESPACE mc)

add_subdirectory(3rd_party/Catch2 EXCLUDE_FROM_ALL)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    enable_testing()
    include(CTest)
    list (APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/3rd_party/Catch2/extras)
    include(Catch)

    juce_add_console_app(${PROJECT_NAME}_tests PRODUCT_NAME "${PROJECT_NAME}_tests" NEEDS_CURL TRUE)
    catch_discover_tests(${PROJECT_NAME}_tests)

    target_sources(${PROJECT_NAME}_tests
        PRIVATE
            MainTest.cpp

            modules/mc_core/container/mc_Registry_Test.cpp
            modules/mc_core/container/mc_Variant_Test.cpp
            modules/mc_core/javascript/mc_JSONUtils_Test.cpp
            modules/mc_core/math/mc_Constants_Test.cpp
            modules/mc_core/math/mc_RangeUtils_Test.cpp
            modules/mc_core/text/mc_Format_Test.cpp
            modules/mc_core/text/mc_TextValueConverters_Test.cpp
            modules/mc_core/thread/mc_ThreadSafeQueue_Test.cpp
            modules/mc_core/time/Duration_Test.cpp
            modules/mc_core/time/mc_TimeUtils_Test.cpp

            modules/mc_data_structures/value_tree/mc_ValueWrapper_Test.cpp

            modules/mc_dsp/attachment/mc_XYPadAttachment_Test.cpp
            modules/mc_dsp/clock/TriggerClock_Test.cpp
            modules/mc_dsp/container/mc_AudioBufferPool_Test.cpp
            modules/mc_dsp/container/mc_AudioBufferUtils_Test.cpp
            modules/mc_dsp/processor/mc_MultiMonoIIR_Test.cpp
            modules/mc_dsp/processor/mc_StereoWidth_Test.cpp
            modules/mc_dsp/util/mc_BusesLayoutUtils_Test.cpp

            modules/mc_graphics/color/mc_ColorUtils_Test.cpp
            modules/mc_graphics/geometry/mc_GeometryUtils_Test.cpp
            modules/mc_graphics/images/mc_ImageUtils_Test.cpp

            modules/mc_gui_basics/attachment/mc_BipolarFilterAttachment_Test.cpp
            modules/mc_gui_basics/attachment/mc_LabelAttachment_Test.cpp
            modules/mc_gui_basics/attachment/mc_SliderAttachment_Test.cpp
            modules/mc_gui_basics/attachment/mc_TextBoxSliderAttachment_Test.cpp

            modules/mc_gui_basics/widget/mc_BipolarFilter_Test.cpp
            modules/mc_gui_basics/widget/mc_TextBoxSlider_Test.cpp
            modules/mc_gui_basics/widget/mc_XYPad_Test.cpp
    )

    target_compile_definitions(${PROJECT_NAME}_tests
        PRIVATE
            JUCE_WEB_BROWSER=0
            JUCE_USE_OGGVORBIS=0
            JUCE_DISABLE_JUCE_VERSION_PRINTING=1
    )

    target_link_libraries(${PROJECT_NAME}_tests
        PRIVATE
            mc::mc_external
            mc::mc_core
            mc::mc_data_structures
            mc::mc_dsp
            mc::mc_graphics
            mc::mc_gui_basics
            mc::mc_meters
            Catch2::Catch2
            juce::juce_recommended_config_flags
            ModernCircuits::CompilerOptions
            ModernCircuits::CompilerWarnings
            ModernCircuits::CodeCoverage
    )
endif()
