/*
  ==============================================================================

    TonalVoice.h
    Created: 11 Nov 2019 9:36:34pm
    Author:  除村 武志

  ==============================================================================
*/

#pragma once
#include "BaseVoice.h"

#define NUMNOTEBUFFER 10

struct TonalVoice : public BaseVoice   // The base for Pulse and Triangle
{
    TonalVoice (SettingRefs* sRefs);
    float voltageForAngle (double angle) override = 0;

    // Vibrato
    double vibratoPhase = 0;
    double vibratoPhaseDelta = 0;

    // BendState
    double currentBendAmount = 0;

    // Auto Bend
    double currentAutoBendAmount = 0;
    double autoBendDelta = 0;

    // Vibrato
    int vibratoCount;
    double currentModWheelValue;
    double getVibratoPhase();

    // Custom Pitch/Note states
    int currentPitchSequenceFrame = 0;
    
    // Legato/Arpeggio
    int noteBuffer[NUMNOTEBUFFER];
    int currentNumNoteBuffer = 0;
    int primaryMidiChannel = 1;

    // Legato
    double portamentoTime = 0;

    // Arpeggio
    int currentArpeggioFrame = 0;
    double arpeggioFrameTimer = 0;
    double arpeggioFrameLength = 0; // Unit: seconds. Set non-zero value to enable arpeggio
    int retireBuffer[NUMNOTEBUFFER];
    int currentNumRetireBuffer = 0;

    void startNote (int midiNoteNumber, float velocity,
                    SynthesiserSound*, int currentPitchWheelPosition) override;
    void advanceControlFrame() override;
    void calculateAngleDelta() override;
    void pitchWheelMoved (int) override;
    void controllerMoved (int, int) override;

    void setLegatoMode(double time, int midiCh);
    void addLegatoNote (int midiNoteNumber, float velocity);
    int removeLegatoNote(int midiNoteNumber);

    void setArpeggioMode(double interval, int midiCh);
    void addArpeggioNoteAscending(int midiNoteNumber);
    void addArpeggioNoteDescending(int midiNoteNumber);
    int removeArpeggioNote(int midiNoteNumber);
    
    void pushNoteBuffer(int index, int value);
    void shiftNoteBuffer(int index);

    double noteNoToHeltzDouble (double noteNoInDouble, const double frequencyOfA = 440);

    void onFrameAdvanced() override;

    bool isArpeggioEnabled() {
        return arpeggioFrameLength > 0;
    }
    bool isInReleasePhase();
};
