cmake_minimum_required(VERSION 3.15)
set(PLUGIN_NAME "Magical8bitPlug2")
string(TOLOWER ${PLUGIN_NAME} PLUGIN_NAME_LOWERCASE)
project(${PLUGIN_NAME}_project VERSION 1.1.0)

option(PLUGIN_VST3 "Build VST3 Plugin" OFF)
option(PLUGIN_LV2 "Build LADSPA Version 2 Plugin" OFF)

#find_package(JUCE CONFIG REQUIRED) # You need to install compiled JUCE framework to your system.
# Or,
add_subdirectory(modules/JUCE) # JUCE framework on a subdirectory.

set(PLUGIN_FORMATS Standalone)
if(PLUGIN_VST3)
  list(APPEND PLUGIN_FORMATS VST3)
endif()
if(PLUGIN_LV2)
  list(APPEND PLUGIN_FORMATS LV2)
endif()

message(STATUS "JUCE Formats: ${PLUGIN_FORMATS}")

juce_add_plugin(${PLUGIN_NAME}
  PLUGIN_NAME ${PLUGIN_NAME}
  PRODUCT_NAME ${PLUGIN_NAME_LOWERCASE}
  VERSION ${CMAKE_PROJECT_VERSION}
  BUNDLE_ID "com.ymck.magical8bitPlug2Juce"
  ICON_SMALL "../Resources/icon-256.png"
  ICON_LARGE "../Resources/icon-512.png"
  COMPANY_NAME "Ymck"
  COMPANY_WEBSITE "http://ymck.net"
  COMPANY_EMAIL "info@ymck.net"
  IS_SYNTH TRUE
  NEEDS_MIDI_INPUT TRUE
  NEEDS_MIDI_OUTPUT FALSE
  IS_MIDI_EFFECT FALSE
  PLUGIN_MANUFACTURER_CODE "Ymck"
  PLUGIN_CODE "synj"
  FORMATS ${PLUGIN_FORMATS}
  LV2_URI "http://ymck.net"
  DESCRIPTION "8bit sound generator 2nd ver. by YMCK"
)

# Generate JuceHeader.h
juce_generate_juce_header(${PLUGIN_NAME})

target_compile_definitions(${PLUGIN_NAME}
  PUBLIC
    JUCE_JACK=1
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_DISPLAY_SPLASH_SCREEN=1
    JUCE_USE_DARK_SPLASH_SCREEN=0
    JUCE_REPORT_APP_USAGE=0
    JUCE_VST3_CAN_REPLACE_VST2=0
    JUCE_STRICT_REFCOUNTEDPOINTER=1
)

target_sources(${PLUGIN_NAME}
  PRIVATE
    ../Source/CheckBoxComponent.cpp
    ../Source/ChoiceComponent.cpp
    ../Source/CustomEnvelopeComponent.cpp
    ../Source/SliderComponent.cpp
    ../Source/AdvancedParamsComponent.cpp
    ../Source/BasicParamsComponent.cpp
    ../Source/BendParamsComponent.cpp
    ../Source/EnvelopeParamsComponent.cpp
    ../Source/MonophonicComponent.cpp
    ../Source/NoiseParamsComponent.cpp
    ../Source/PulseParamsComponent.cpp
    ../Source/SweepParamsComponent.cpp
    ../Source/VibratoParamsComponent.cpp
    ../Source/CustomSynth.cpp
    ../Source/FrameSequenceParseErrors.cpp
    ../Source/FrameSequenceParser.cpp
    ../Source/ColorScheme.cpp
    ../Source/BaseVoice.cpp
    ../Source/NoiseVoice.cpp
    ../Source/TriangleVoice.cpp
    ../Source/PulseVoice.cpp
    ../Source/TonalVoice.cpp
    ../Source/Settings.cpp
    ../Source/Voices.cpp
    ../Source/PluginProcessor.cpp
    ../Source/PluginEditor.cpp
)

juce_add_binary_data(${PLUGIN_NAME}_images
  SOURCES
    ../Resources/icon-256.png
    ../Resources/icon-512.png
)

set_target_properties(${PLUGIN_NAME}_images
  PROPERTIES
    POSITION_INDEPENDENT_CODE TRUE
)

# JUCE Modules and Binary Data
target_link_libraries(${PLUGIN_NAME}
  PRIVATE
    juce::juce_audio_basics
    juce::juce_audio_devices
    juce::juce_audio_formats
    juce::juce_audio_plugin_client
    juce::juce_audio_processors
    juce::juce_audio_utils
    juce::juce_core
    juce::juce_cryptography
    juce::juce_data_structures
    juce::juce_events
    juce::juce_graphics
    juce::juce_gui_basics
    juce::juce_gui_extra
    juce::juce_opengl
    ${PLUGIN_NAME}_images
)

# Recommended Flags
target_link_libraries(${PLUGIN_NAME}
  PUBLIC
    juce::juce_recommended_warning_flags
    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags
)
