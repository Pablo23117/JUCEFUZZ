cmake_minimum_required(VERSION 3.22)

project(JUCE_ZIP_READ_HARNESS VERSION 0.0.1)

find_package(JUCE CONFIG REQUIRED)  

juce_add_console_app(JuceZipHarness
    PRODUCT_NAME "Console App Example")    

target_sources(JuceZipHarness
    PRIVATE
        zip-harness.cpp)

target_compile_definitions(JuceZipHarness
    PRIVATE
        JUCE_WEB_BROWSER=0 
        JUCE_USE_CURL=0
        JUCE_USE_FLAC=0)

target_link_libraries(JuceZipHarness
    PRIVATE
        juce::juce_core
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_warning_flags)