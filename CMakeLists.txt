cmake_minimum_required(VERSION 3.15)
cmake_policy(VERSION 3.15)
project(modern-circuits-juce-modules VERSION 0.1.0)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    find_program(CCACHE ccache)
    if (CCACHE)
        set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE})
    endif ()

    set(CMAKE_C_STANDARD 11)
    set(CMAKE_C_STANDARD_REQUIRED ON)
    set(CMAKE_C_EXTENSIONS OFF)

    if(NOT "${CMAKE_CXX_STANDARD}")
        set(CMAKE_CXX_STANDARD 14)
    endif()
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)

    if(NOT "${CMAKE_OSX_DEPLOYMENT_TARGET}")
        set(CMAKE_OSX_DEPLOYMENT_TARGET "10.11")
    endif()

    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
endif ()

add_subdirectory(3rd_party/lib-stl)
add_subdirectory(3rd_party/JUCE EXCLUDE_FROM_ALL)
juce_add_module(modules/mc_core             ALIAS_NAMESPACE mc)
juce_add_module(modules/mc_data_structures  ALIAS_NAMESPACE mc)
juce_add_module(modules/mc_dsp              ALIAS_NAMESPACE mc)
juce_add_module(modules/mc_graphics         ALIAS_NAMESPACE mc)
juce_add_module(modules/mc_gui_basics       ALIAS_NAMESPACE mc)
juce_add_module(modules/mc_meters           ALIAS_NAMESPACE mc)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    enable_testing()
    include(CTest)

    juce_add_console_app(${PROJECT_NAME}_tests PRODUCT_NAME "${PROJECT_NAME}_tests" NEEDS_CURL TRUE)
    catch_discover_tests(${PROJECT_NAME}_tests)

    target_sources(${PROJECT_NAME}_tests
        PRIVATE
            MainTest.cpp

            modules/mc_core/container/Registry.test.cpp
            modules/mc_core/javascript/JSONUtils.test.cpp
            modules/mc_core/math/RangeUtils.test.cpp
            modules/mc_core/text/Format.test.cpp
            modules/mc_core/text/TextValueConverters.test.cpp
            modules/mc_core/time/Duration.test.cpp
            modules/mc_core/time/TimeUtils.test.cpp

            modules/mc_data_structures/value_tree/ValueWrapper.test.cpp

            modules/mc_dsp/algorithm/downSample.test.cpp
            modules/mc_dsp/attachment/XYPadAttachment.test.cpp
            modules/mc_dsp/clock/TriggerClock.test.cpp
            modules/mc_dsp/container/AudioBufferPool.test.cpp
            modules/mc_dsp/container/AudioBufferUtils.test.cpp
            modules/mc_dsp/processor/MultiMonoIIR.test.cpp
            modules/mc_dsp/processor/StereoWidth.test.cpp
            modules/mc_dsp/util/BusesLayoutUtils.test.cpp

            modules/mc_graphics/color/ColorUtils.test.cpp
            modules/mc_graphics/geometry/GeometryUtils.test.cpp
            modules/mc_graphics/images/ImageUtils.test.cpp

            modules/mc_gui_basics/attachment/BipolarFilterAttachment.test.cpp
            modules/mc_gui_basics/attachment/LabelAttachment.test.cpp
            modules/mc_gui_basics/attachment/SliderAttachment.test.cpp
            modules/mc_gui_basics/attachment/TextBoxSliderAttachment.test.cpp

            modules/mc_gui_basics/widget/BipolarFilter.test.cpp
            modules/mc_gui_basics/widget/TextBoxSlider.test.cpp
            modules/mc_gui_basics/widget/XYPad.test.cpp
    )

    target_compile_definitions(${PROJECT_NAME}_tests
        PRIVATE
            JUCE_WEB_BROWSER=0
            JUCE_USE_OGGVORBIS=0
            JUCE_DISABLE_JUCE_VERSION_PRINTING=1
    )

    target_link_libraries(${PROJECT_NAME}_tests
        PRIVATE
            mc::mc_stl
            mc::mc_core
            mc::mc_data_structures
            mc::mc_dsp
            mc::mc_graphics
            mc::mc_gui_basics
            mc::mc_meters
            mc::compiler_options
            mc::compiler_warnings
            mc::coverage
            Catch2::Catch2
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
endif()

