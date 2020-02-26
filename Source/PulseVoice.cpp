/*
  ==============================================================================

    PulseVoice.cpp
    Created: 11 Nov 2019 9:36:51pm
    Author:  除村 武志

  ==============================================================================
*/

#include "PulseVoice.h"

//---------------------------------------------
//
// Pulse Voice
//
//---------------------------------------------
PulseVoice::PulseVoice (SettingRefs* sRefs) : TonalVoice (sRefs) {}

void PulseVoice::startNote (int midiNoteNumber, float velocity, SynthesiserSound*, int currentPitchBendPosition)
{
    TonalVoice::startNote (midiNoteNumber, velocity, 0, currentPitchBendPosition);

    currentDutySequenceFrame = 0;
    currentDuty = (PulseDuty) ((int) (*settingRefs->duty));
}

float PulseVoice::voltageForAngle (double angle)
{
    float rate = 1.0;

    switch (currentDuty)
    {
        case kPulseDuty125:
            rate = 0.25;
            break;

        case kPulseDuty250:
            rate = 0.50;
            break;

        case kPulseDuty500:
            rate = 1.00;
            break;

        default:
            break;
    }

    return angle < rate * MathConstants<float>::pi ? -1.0 : 1.0;
}

void PulseVoice::advanceControlFrame()
{
    TonalVoice::advanceControlFrame();

    if (settingRefs->isDutySequenceEnabled())
    {
        currentDutySequenceFrame = settingRefs->dutySequence.nextIndexOf (currentDutySequenceFrame);
        currentDuty = (PulseDuty)settingRefs->dutySequence.valueAt (currentDutySequenceFrame);
    }
}
