project(mc_core VERSION 0.1.0)

juce_add_console_app(${PROJECT_NAME}_tests PRODUCT_NAME "${PROJECT_NAME}_tests")
catch_discover_tests(${PROJECT_NAME}_tests)

target_sources(${PROJECT_NAME}_tests
    PRIVATE
        main_test.cpp

        text/format_test.cpp
)

target_compile_definitions(${PROJECT_NAME}_tests
    PRIVATE
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
)

target_link_libraries(${PROJECT_NAME}_tests
    PRIVATE
        mc::mc_core
        Catch2::Catch2
        fmt::fmt
    PUBLIC
        juce::juce_recommended_config_flags
        # juce::juce_recommended_warning_flags
)

