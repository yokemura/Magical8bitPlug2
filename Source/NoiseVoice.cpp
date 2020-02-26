/*
  ==============================================================================

    NoiseVoice.cpp
    Created: 11 Nov 2019 9:37:21pm
    Author:  除村 武志

  ==============================================================================
*/

#include "NoiseVoice.h"

//---------------------------------------------
//
// Noise Voice
//
//---------------------------------------------
NoiseVoice::NoiseVoice(SettingRefs *sRefs) : TonalVoice(sRefs) {}

void NoiseVoice::startNote(int midiNoteNumber, float velocity, SynthesiserSound *, int currentPitchBendPosition) {
    TonalVoice::startNote(midiNoteNumber, velocity, 0, currentPitchBendPosition);
    switch (settingRefs->noiseAlgorithm()) {
        case kNoiseInfinite2:
            cycleLength = MathConstants<float>::pi / 25.0;
            break;

        case kNoiseLong:
        case kNoiseShort:
            cycleLength = MathConstants<float>::pi / 8.0;
            break;

        default:
            cycleLength = MathConstants<float>::pi / 8.0;
            break;
    }
}

float NoiseVoice::voltageForAngle (double angle)
{
    // TODO: StartVoice側でangleDeltaを調整する方が良い
    //    double dividedAngle = fmod(angle, MathConstants<float>::pi / 2.0);
    bool isNewCycle = angle < previousAngle;
    bool shouldUpdate = false;

    if (isNewCycle)
    {
        shouldUpdate = true;
    }
    else if (nextAngle != 0)
    {
        if (angle >= nextAngle)
        {
            shouldUpdate = true;
        }
    }

    if (shouldUpdate)
    {
        if (settingRefs->noiseAlgorithm() == kNoiseInfinite2)
        {
            currentVoltage = float (rand() % 16 - 8) / 16.;
        }
        else
        {
            int compareBitPos = settingRefs->noiseAlgorithm() == kNoiseLong ? 1 : 6;

            unsigned int bit0 = rgstr & 0b0000001;
            unsigned int compared = (rgstr & 1 << compareBitPos) >> compareBitPos;
            unsigned int feedback = bit0 ^ compared;

            rgstr = rgstr >> 1;

            unsigned int mask = ~ (1 << 14);
            unsigned int writeback = feedback << 14;
            rgstr = (rgstr & mask) | writeback;

            currentVoltage = (float)bit0 - 0.5;
        }

        nextAngle = (double) ((int) (angle / cycleLength) + 1) * cycleLength;

        if (nextAngle >= MathConstants<float>::pi * 2) { nextAngle = 0; }
    }

    previousAngle = angle;

    return currentVoltage;
}
