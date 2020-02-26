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

    void startNote (int midiNoteNumber, float velocity,
                    SynthesiserSound*, int currentPitchWheelPosition) override;
    void advanceControlFrame() override;
    void calculateAngleDelta() override;
    void pitchWheelMoved (int) override;
    void controllerMoved (int, int) override;

    double noteNoToHeltzDouble (double noteNoInDouble, const double frequencyOfA = 440);

    void onFrameAdvanced() override;
};
