/*
  ==============================================================================

    BaseVoice.h
    Created: 11 Nov 2019 9:38:44pm
    Author:  除村 武志

  ==============================================================================
*/

#pragma once
#include "Voices.h"

struct BaseVoice : public SynthesiserVoice
{
    SettingRefs* settingRefs;

    BaseVoice (SettingRefs* sRefs);

    bool canPlaySound (SynthesiserSound* sound) override;
    void startNote (int midiNoteNumber, float velocity,
                    SynthesiserSound*, int currentPitchWheelPosition) override;
    void stopNote (float /*velocity*/, bool allowTailOff) override;
    void pitchWheelMoved (int) override      {}
    void controllerMoved (int, int) override {}
    void renderNextBlock (AudioSampleBuffer& outputBuffer, int startSample, int numSamples) override;

    virtual float voltageForAngle (double angle) = 0;
    virtual void onFrameAdvanced() {};
    virtual void advanceControlFrame();
    virtual void calculateAngleDelta();

protected:
    // Basic
    int noteNumber;
    float ampByVelocityAndGain = 1.0;

    // Oscillator State
    double currentAngle = 0.0;
    double angleDelta = 0.0;

    // Envelope
    double currentEnvelopeLevel = 0.0;
    EnvelopePhase envelopePhase = kEnvelopePhaseA;
    double attack_slope = 1.0;
    double decay_slope = 0.0; // Positive to decrease
    double sustain_level = 1.0;
    double release_slope = 1.0; // Positive to decrease

    // For Frame Counting for Customs
    double controlFrameTimer = 0;
    const double controlFrameLength = 1.0 / 60.0;
    int currentVolumeSequenceFrame = 0;
};
