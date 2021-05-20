/*
  ==============================================================================

    TonalVoice.h
    Created: 11 Nov 2019 9:36:34pm
    Author:  除村 武志

  ==============================================================================
*/

#pragma once
#include "BaseVoice.h"

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
    int noteBuffer[10];
    int currentNumNoteBuffer = 0;

    // Legato
    double portamentoTime = 0;

    // Arpeggio
    int currentArpeggioFrame = 0;
    double arpeggioFrameTimer = 0;
    double arpeggioFrameLength = 0; // Unit: seconds. Set non-zero value to enable arpeggio

    void startNote (int midiNoteNumber, float velocity,
                    SynthesiserSound*, int currentPitchWheelPosition) override;
    void advanceControlFrame() override;
    void calculateAngleDelta() override;
    void pitchWheelMoved (int) override;
    void controllerMoved (int, int) override;

    void setLegatoMode(double time);
    void addLegatoNote (int midiNoteNumber, float velocity);
    int removeLegatoNote(int midiNoteNumber);

    void setArpeggioMode(double interval);
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
    
    /*
    void testArpeggioNotes() {
        startNote(100, 1, NULL, 0);
        
        setArpeggioMode(1.0);
        jassert(isArpeggioEnabled());
        jassert(arpeggioNotes[0] == 100);
        jassert(currentNumArpeggioNotes == 1);
        
        addArpeggioNoteAscending(90);
        jassert(arpeggioNotes[0] == 90);
        jassert(arpeggioNotes[1] == 100);
        jassert(currentNumArpeggioNotes == 2);
        
        addArpeggioNoteAscending(95);
        jassert(arpeggioNotes[0] == 90);
        jassert(arpeggioNotes[1] == 95);
        jassert(arpeggioNotes[2] == 100);
        jassert(currentNumArpeggioNotes == 3);

        jassert(removeArpeggioNote(92) == 3);
        jassert(arpeggioNotes[0] == 90);
        jassert(arpeggioNotes[1] == 95);
        jassert(arpeggioNotes[2] == 100);

        jassert(removeArpeggioNote(100) == 2);
        jassert(arpeggioNotes[0] == 90);
        jassert(arpeggioNotes[1] == 95);

        jassert(removeArpeggioNote(90) == 1);
        jassert(arpeggioNotes[0] == 95);

        jassert(removeArpeggioNote(95) == 0);
        
        
        startNote(100, 1, NULL, 0);
        
        setArpeggioMode(1.0);
        jassert(isArpeggioEnabled());
        jassert(arpeggioNotes[0] == 100);
        jassert(currentNumArpeggioNotes == 1);
        
        addArpeggioNoteDescending(90);
        jassert(arpeggioNotes[0] == 100);
        jassert(arpeggioNotes[1] == 90);
        jassert(currentNumArpeggioNotes == 2);
        
        addArpeggioNoteDescending(95);
        jassert(arpeggioNotes[0] == 100);
        jassert(arpeggioNotes[1] == 95);
        jassert(arpeggioNotes[2] == 90);
        jassert(currentNumArpeggioNotes == 3);

        jassert(removeArpeggioNote(92) == 3);
        jassert(arpeggioNotes[0] == 100);
        jassert(arpeggioNotes[1] == 95);
        jassert(arpeggioNotes[2] == 90);

        jassert(removeArpeggioNote(100) == 2);
        jassert(arpeggioNotes[0] == 95);
        jassert(arpeggioNotes[1] == 90);

        jassert(removeArpeggioNote(90) == 1);
        jassert(arpeggioNotes[0] == 95);

        jassert(removeArpeggioNote(95) == 0);
    }
     */
};
