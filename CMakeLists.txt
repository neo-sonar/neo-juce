cmake_minimum_required(VERSION 3.15)
cmake_policy(VERSION 3.15)

project(modern-circuits-juce-modules VERSION 0.1.0)

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

add_subdirectory(3rd_party/fmt EXCLUDE_FROM_ALL)
add_subdirectory(3rd_party/JUCE EXCLUDE_FROM_ALL)
add_subdirectory(3rd_party/Catch2 EXCLUDE_FROM_ALL)

juce_add_module(modules/mc_core ALIAS_NAMESPACE mc)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    list (APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/3rd_party/Catch2/extras")
    enable_testing()
    include(CTest)
    include(Catch)

    add_subdirectory(modules/mc_core)
endif()
