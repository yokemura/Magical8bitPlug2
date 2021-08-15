/*
  ==============================================================================

    PulseVoice.h
    Created: 11 Nov 2019 9:36:51pm
    Author:  除村 武志

  ==============================================================================
*/

#pragma once
#include "TonalVoice.h"

struct PulseVoice : public TonalVoice
{

    PulseVoice (SettingRefs* sRefs);

    PulseDuty currentDuty = kPulseDuty500; // May be changed by Duty Sequence

    // Custom Duty Sequence states
    int currentDutySequenceFrame = 0;

    void startNote (int midiNoteNumber, float velocity,
                    SynthesiserSound*, int currentPitchWheelPosition) override;
    float voltageForAngle (double angle) override;
    void advanceControlFrame() override;
    void stopNote(float velocity, bool allowTailOff) override;
};
