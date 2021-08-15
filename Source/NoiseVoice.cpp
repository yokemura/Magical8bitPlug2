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
    //TonalVoice::startNote(midiNoteNumber, velocity, 0, currentPitchBendPosition);
    int midiNote = midiNoteNumber;
    int midiNoteRange[16] = { 5, 17, 29, 34, 41, 46, 53, 57, 61, 65, 70, 77, 89, 101, 113, 125 };
    switch (settingRefs->noiseAlgorithm()) {
        case kNoiseInfinite2:
            cycleLength = MathConstants<float>::pi / 25.0;
            break;

        case kNoiseLong:
        case kNoiseShort:
            cycleLength = MathConstants<float>::pi / 8.0;
            break;

        case kNoiseLongNes:
        case kNoiseShortNes:
            cycleLength = MathConstants<float>::pi / 20.175;
            //rgstr = 0x8000;
            //rgstr = rand();
            midiNote = midiNoteRange[(midiNote + 8) % 16];
            break;

        default:
            cycleLength = MathConstants<float>::pi / 8.0;
            break;
    }
    TonalVoice::startNote(midiNote, velocity, 0, currentPitchBendPosition);
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
            currentVoltage = float (rand() % 16 - 8) / 16.0;
            //currentVoltage = float(rand() % 16 - 7.5) / 15.0;
        }
        else  if (settingRefs->noiseAlgorithm() == kNoiseLong || settingRefs->noiseAlgorithm() == kNoiseShort)
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
        else
        {
            int shortFreq = settingRefs->noiseAlgorithm() == kNoiseLongNes ? 1 : 6;

            rgstr >>= 1;
            rgstr |= ((rgstr ^ (rgstr >> shortFreq)) & 1) << 15;
            currentVoltage = (float)(rgstr & 1) - 0.5;
        }

        nextAngle = (double) ((int) (angle / cycleLength) + 1) * cycleLength;

        if (nextAngle >= MathConstants<float>::pi * 2) { nextAngle = 0; }
    }

    previousAngle = angle;

    return currentVoltage;
}
