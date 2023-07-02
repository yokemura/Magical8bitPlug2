/*
  ==============================================================================

    Settings.h
    Created: 23 May 2019 11:54:44am
    Author:  除村 武志

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "ColorScheme.h"
#include "FrameSequence.h"
#include "FrameSequenceParseErrors.h"

//---------------------------------------------
//
// Plugin Global
//
//---------------------------------------------
enum VoiceType
{
    kVoiceTypePulse = 0,
    kVoiceTypeTriangle,
    kVoiceTypeNoise
};

struct PluginSettings
{
    VoiceType type = kVoiceTypePulse;
    int maxPoly = 1;
    double gain = 1.0;
    double arpeggioTime = 0;
    double bendRange = 2;
};

//---------------------------------------------
//
// Monophonic Options
//
//---------------------------------------------
enum MonophonicBehavior
{
    kLegato = 0,
    kArpeggioUp,
    kArpeggioDown,
    kNonLegato,
};

enum ArpeggioIntervalType
{
    k1frame = 0,
    k2frames,
    k3frames,
    k96th,
    k64th,
    k48th,
    k32nd,
    k24th,
    kSlider,
};

//---------------------------------------------
//
// Tone Specific
//
//---------------------------------------------
enum PulseDuty
{
    kPulseDuty125 = 0,
    kPulseDuty250,
    kPulseDuty500,
};

enum NoiseAlgorithm
{
    kNoiseInfinite2 = 0,
    kNoiseLong,
    kNoiseShort,
};

enum PitchSequenceMode
{
    kPitchSequenceModeCoarse = 0,
    kPitchSequenceModeFine
};

class FrameSequenceChangeListener
{
public:
    FrameSequenceChangeListener() {}
    virtual ~FrameSequenceChangeListener() {};
    virtual void sequenceChanged (String& str) {};
};


struct FrameSequenceParseException
{
    String message;
    bool isFatal;

    FrameSequenceParseException (String mes, bool fatalFlag)
    {
        message = mes;
        isFatal = fatalFlag;
    }
};

struct SettingRefs
{
    // Meta
    float* isAdvancedPanelOpen_raw = nullptr;
    float* colorScheme = nullptr;
    // Basic
    float* osc = nullptr;
    float* gain = nullptr;
    float* maxPoly = nullptr;
    // ADSR
    float* attack = nullptr;
    float* decay = nullptr;
    float* suslevel = nullptr;
    float* release = nullptr;
    // Monophonic
    float* monophonicBehavior_raw = nullptr;
    float* arpeggioIntervalType_raw = nullptr;
    float* arpeggioIntervalSliderValue = nullptr;
    float* portamentoTime = nullptr;
    // Bend
    float* bendRange = nullptr;
    // Vibrato
    float* vibratoRate = nullptr;
    float* vibratoDepth = nullptr;
    float* vibratoDelay = nullptr;
    float* vibratoIgnoresWheel_raw = nullptr;
    // Sweep
    float* sweepInitialPitch = nullptr;
    float* sweepTime = nullptr;
    // For Pulse
    float* duty = nullptr;
    // For Noise
    float* noiseAlgorithm_raw = nullptr;
    float* restrictsToNESFrequency_raw = nullptr;
    // Sequence
    float* isVolumeSequenceEnabled_raw = nullptr;
    float* isPitchSequenceEnabled_raw = nullptr;
    float* isDutySequenceEnabled_raw = nullptr;
    float* pitchSequenceMode_raw = nullptr;
    //pitch resolution
    float* restrictPitchBend_raw = nullptr;
    float* restrictAutoBend_raw = nullptr;

    FrameSequence volumeSequence;
    FrameSequence pitchSequence;
    FrameSequence dutySequence;
    String volumeSequenceString = "";
    String pitchSequenceString = "";
    String dutySequenceString = "";

    bool setSequenceWithString (const String& type, const String& input, ParseError* error);
    String& getSequenceString (const String& type);

    FrameSequence parseSequenceString (const String& input);
    FrameSequenceChangeListener* volumeSequenceListener = nullptr;
    FrameSequenceChangeListener* pitchSequenceListener = nullptr;
    FrameSequenceChangeListener* dutySequenceListener = nullptr;

    //
    // accessors
    //
    int oscillatorType() { return (int) (*osc); }
    bool isMonophonic() { return (int)(*maxPoly) == 1; }
    bool isAdvancedPanelOpen() { return *isAdvancedPanelOpen_raw > 0.5; }
    ColorSchemeType colorSchemeType() { return (ColorSchemeType) ((int) (*colorScheme)); }

    NoiseAlgorithm noiseAlgorithm() { return (NoiseAlgorithm) ((int) (*noiseAlgorithm_raw)); }

    bool vibratoIgnoresWheel() { return *vibratoIgnoresWheel_raw > 0.5; }

    bool isVolumeSequenceEnabled() { return *isVolumeSequenceEnabled_raw > 0.5; }
    bool isPitchSequenceEnabled() { return *isPitchSequenceEnabled_raw > 0.5; }
    bool isDutySequenceEnabled() { return *isDutySequenceEnabled_raw > 0.5; }
    
    bool isRestrictingPitchBend() {return *restrictPitchBend_raw > 0.5;}
    bool isRestrictingAutoBend() {return *restrictAutoBend_raw > 0.5;}
    PitchSequenceMode pitchSequenceMode() { return (PitchSequenceMode) ((int) (*pitchSequenceMode_raw)); }
    MonophonicBehavior monophonicBehavior() { return (MonophonicBehavior) ((int) (*monophonicBehavior_raw)); }
    ArpeggioIntervalType apreggioIntervalType() { return (ArpeggioIntervalType) ((int) (*arpeggioIntervalType_raw)); }

    //
    // constructor
    //
    SettingRefs (AudioProcessorValueTreeState* parameters)
    {
        // Meta
        isAdvancedPanelOpen_raw = (float*) parameters->getRawParameterValue ("isAdvancedPanelOpen_raw");
        colorScheme = (float*) parameters->getRawParameterValue ("colorScheme");
        // Basic
        osc = (float*) parameters->getRawParameterValue ("osc");
        gain = (float*) parameters->getRawParameterValue ("gain");
        maxPoly = (float*) parameters->getRawParameterValue ("maxPoly");
        // ADSR
        attack = (float*) parameters->getRawParameterValue ("attack");
        decay = (float*) parameters->getRawParameterValue ("decay");
        suslevel = (float*) parameters->getRawParameterValue ("suslevel");
        release = (float*) parameters->getRawParameterValue ("release");
        // Monophonic
        monophonicBehavior_raw = (float*) parameters->getRawParameterValue ("monophonicBehavior_raw");
        arpeggioIntervalType_raw = (float*) parameters->getRawParameterValue ("arpeggioIntervalType_raw");
        arpeggioIntervalSliderValue = (float*) parameters->getRawParameterValue ("arpeggioIntervalSliderValue");
        portamentoTime = (float*) parameters->getRawParameterValue ("portamentoTime");
        // Bend
        bendRange = (float*) parameters->getRawParameterValue ("bendRange");
        // Vibrato
        vibratoRate = (float*) parameters->getRawParameterValue ("vibratoRate");
        vibratoDepth = (float*) parameters->getRawParameterValue ("vibratoDepth");
        vibratoDelay = (float*) parameters->getRawParameterValue ("vibratoDelay");
        vibratoIgnoresWheel_raw = (float*) parameters->getRawParameterValue ("vibratoIgnoresWheel_raw");
        // Sweep
        sweepInitialPitch = (float*) parameters->getRawParameterValue ("sweepInitialPitch");
        sweepTime = (float*) parameters->getRawParameterValue ("sweepTime");
        // For Pulse
        duty = (float*) parameters->getRawParameterValue ("duty");
        // For Noise
        noiseAlgorithm_raw = (float*) parameters->getRawParameterValue ("noiseAlgorithm_raw");
        restrictsToNESFrequency_raw = (float*) parameters->getRawParameterValue ("restrictsToNESFrequency_raw");
        // Sequence
        isVolumeSequenceEnabled_raw = (float*) parameters->getRawParameterValue ("isVolumeSequenceEnabled_raw");
        isPitchSequenceEnabled_raw = (float*) parameters->getRawParameterValue ("isPitchSequenceEnabled_raw");
        isDutySequenceEnabled_raw = (float*) parameters->getRawParameterValue ("isDutySequenceEnabled_raw");
        pitchSequenceMode_raw = (float*) parameters->getRawParameterValue ("pitchSequenceMode_raw");
        //Pitch resolution
        restrictPitchBend_raw = (float*) parameters->getRawParameterValue("restrictPitchBend_raw");
        restrictAutoBend_raw = (float*) parameters->getRawParameterValue("restrictAutoBend_raw");
    }
};
