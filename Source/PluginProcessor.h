/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Settings.h"
#include "Voices.h"
#include "CustomSynth.h"


//==============================================================================
struct GenericSound   : public SynthesiserSound
{
    GenericSound() {}

    bool appliesToNote    (int) override        { return true; }
    bool appliesToChannel (int) override        { return true; }
};

//==============================================================================
/**
*/
class Magical8bitPlug2AudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    Magical8bitPlug2AudioProcessor();
    ~Magical8bitPlug2AudioProcessor();

    //==============================================================================
    float noteOnVel;

    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
#endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //==============================================================================
    void setupVoice();

    AudioProcessorValueTreeState parameters;
    SettingRefs settingRefs;

private:
    //==============================================================================
    CustomSynth synth;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Magical8bitPlug2AudioProcessor)
};
