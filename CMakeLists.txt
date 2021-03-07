cmake_minimum_required(VERSION 3.15)
cmake_policy(VERSION 3.15)

project(modern-circuits-juce-modules VERSION 0.1.0)

option(MODERN_CIRCUITS_BUILD_COVERAGE "Build with coverage enabled" OFF)
option(MODERN_CIRCUITS_BUILD_ASAN "Build with address sanitizer enabled" OFF)
option(MODERN_CIRCUITS_BUILD_UBSAN "Build with undefined behavior sanitizer enabled" OFF)
option(MODERN_CIRCUITS_BUILD_TSAN "Build with thread sanitizer enabled" OFF)
option(MODERN_CIRCUITS_BUILD_MSAN "Build with memory sanitizer enabled" OFF)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(CMAKE_C_STANDARD 11)
    set(CMAKE_C_STANDARD_REQUIRED ON)
    set(CMAKE_C_EXTENSIONS OFF)

    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)

    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
    set(CMAKE_CXX_VISIBILITY_PRESET hidden)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
    set(BUILD_SHARED_LIBS OFF)

    find_program(CCACHE ccache)
    if (CCACHE)
        set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE})
    endif ()
endif ()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(mcCompilerOptions)
include(mcCompilerWarnings)
include(mcCodeCoverage)

add_subdirectory(3rd_party/fmt EXCLUDE_FROM_ALL)
add_subdirectory(3rd_party/JUCE EXCLUDE_FROM_ALL)
add_subdirectory(3rd_party/Catch2 EXCLUDE_FROM_ALL)

juce_add_module(modules/mc_core ALIAS_NAMESPACE mc)
juce_add_module(modules/mc_data_structures ALIAS_NAMESPACE mc)
juce_add_module(modules/mc_graphics ALIAS_NAMESPACE mc)
juce_add_module(modules/mc_gui_basics ALIAS_NAMESPACE mc)


if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    list (APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/3rd_party/Catch2/extras")
    enable_testing()
    include(CTest)
    include(Catch)

    juce_add_console_app(${PROJECT_NAME}_tests PRODUCT_NAME "${PROJECT_NAME}_tests")
    catch_discover_tests(${PROJECT_NAME}_tests)

    target_sources(${PROJECT_NAME}_tests
        PRIVATE
            main_test.cpp

            modules/mc_core/container/flat_map_test.cpp
            modules/mc_core/math/range_utils_test.cpp
            modules/mc_core/text/format_test.cpp
            modules/mc_core/time/time_utils_test.cpp

            modules/mc_data_structures/value_tree/value_wrapper_test.cpp

            modules/mc_graphics/color/color_utils_test.cpp
            modules/mc_graphics/geometry/geometry_utils_test.cpp
            modules/mc_graphics/images/image_utils_test.cpp

            modules/mc_gui_basics/attachment/label_attachment_test.cpp
            modules/mc_gui_basics/attachment/slider_attachment_test.cpp
    )

    target_compile_definitions(${PROJECT_NAME}_tests
        PRIVATE
            JUCE_WEB_BROWSER=0
            JUCE_USE_CURL=0
    )

    target_link_libraries(${PROJECT_NAME}_tests
        PRIVATE
            mc::mc_core
            mc::mc_data_structures
            mc::mc_graphics
            mc::mc_gui_basics
            Catch2::Catch2
            fmt::fmt
            juce::juce_recommended_config_flags
            # juce::juce_recommended_warning_flags
            ModernCircuits::CompilerOptions
            ModernCircuits::CompilerWarnings
            ModernCircuits::CodeCoverage
    )
endif()
