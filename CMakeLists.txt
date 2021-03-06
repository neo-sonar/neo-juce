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

    include(FetchContent)
    FetchContent_Declare(catch GIT_REPOSITORY https://github.com/catchorg/Catch2.git GIT_TAG v3.0.0-preview3)
    FetchContent_MakeAvailable(catch)

    list (APPEND CMAKE_MODULE_PATH "${catch_SOURCE_DIR}/extras")
    enable_testing()
    include(CTest)
    include(Catch)

    FetchContent_Declare(juce GIT_REPOSITORY https://github.com/juce-framework/JUCE.git GIT_TAG 6.0.7)
    FetchContent_MakeAvailable(juce)
endif ()

juce_add_module(modules/mc_core ALIAS_NAMESPACE mc)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    add_subdirectory(modules/mc_core)
endif()
