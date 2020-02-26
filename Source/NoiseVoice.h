/*
  ==============================================================================

    NoiseVoice.h
    Created: 11 Nov 2019 9:37:21pm
    Author:  除村 武志

  ==============================================================================
*/

#pragma once
#include "TonalVoice.h"

struct NoiseVoice : public TonalVoice {
    
    NoiseVoice(SettingRefs *sRefs);
    double cycleLength = MathConstants<float>::pi / 8.0;

    // Noise states
    float currentVoltage = -0.5;
    double nextAngle = cycleLength;
    double previousAngle = 0;
    unsigned int rgstr = 0b111111111111111;

    void startNote (int midiNoteNumber, float velocity,
                    SynthesiserSound*, int currentPitchWheelPosition) override;
    float voltageForAngle (double angle) override;
};
