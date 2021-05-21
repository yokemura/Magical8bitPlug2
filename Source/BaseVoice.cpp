/*
  ==============================================================================

    BaseVoice.cpp
    Created: 11 Nov 2019 9:38:44pm
    Author:  除村 武志

  ==============================================================================
*/

#include "BaseVoice.h"

//---------------------------------------------
//
// Base Voice
// (Abstract)
//
//---------------------------------------------
BaseVoice::BaseVoice (SettingRefs* sRefs)
{
    settingRefs = sRefs;
}

bool BaseVoice::canPlaySound (SynthesiserSound* sound)
{
    return true;
}

void BaseVoice::startNote (int midiNoteNumber, float velocity, SynthesiserSound*, int currentPitchBendPosition)
{

    noteNumber = midiNoteNumber;

    envelopePhase = kEnvelopePhaseA;
    currentAngle = 0.0;
    currentEnvelopeLevel = 0.0;

    ampByVelocityAndGain = * (settingRefs->gain) * velocity; // velocity value range is 0.0f-1.0f

    calculateAngleDelta();

    //
    // Envelope
    //
    double srate = getSampleRate();

    if (* (settingRefs->attack) == 0 ) { attack_slope = 1.0; }
    else
    {
        attack_slope = 1.0 / (* (settingRefs->attack) * srate);
    }

    if (* (settingRefs->decay) == 0 ) { decay_slope = 1.0; }
    else
    {
        decay_slope = 1.0 / (* (settingRefs->decay) * srate);
    }

    sustain_level = * (settingRefs->suslevel);

    if (* (settingRefs->release) == 0 ) { release_slope = 1.0; }
    else
    {
        release_slope = 1.0 / (* (settingRefs->release) * srate);
    }

    //
    // Control frame
    //
    controlFrameTimer = 0;
    currentVolumeSequenceFrame = 0;

    if (settingRefs->isVolumeSequenceEnabled())
    {
        currentEnvelopeLevel = (float) (settingRefs->volumeSequence.valueAt (0)) / 15.0f;
    }
}

void BaseVoice::stopNote (float, bool allowTailOff)
{
    if (!allowTailOff)
    {
        clearCurrentNote();
        angleDelta = 0.0;
        return;
    }

    if (settingRefs->isVolumeSequenceEnabled())
    {
        if (settingRefs->volumeSequence.hasRelease)
        {
            if (settingRefs->volumeSequence.isInRelease(currentVolumeSequenceFrame)) {
                // Already in release(Custom Env.)
                return ;
            }
            currentVolumeSequenceFrame = settingRefs->volumeSequence.releaseSequenceStartIndex;
            currentEnvelopeLevel = (float) (settingRefs->volumeSequence.valueAt (0)) / 15.0f;
        }
        else
        {
            clearCurrentNote();
            angleDelta = 0.0;
        }

        return;
    }
    
    if (envelopePhase == kEnvelopePhaseR) {
        // Already in release(ADSR)
        return;
    }

    envelopePhase = kEnvelopePhaseR;
}

void BaseVoice::renderNextBlock (AudioSampleBuffer& outputBuffer, int startSample, int numSamples)
{
    if (getCurrentlyPlayingNote() == -1) {
        return;
    }
    
    if (angleDelta == 0.0)
    {
        return;
    }

    while (--numSamples >= 0)
    {
        //
        // Envelope
        //
        if (settingRefs->isVolumeSequenceEnabled())
        {
            currentEnvelopeLevel = (float) (settingRefs->volumeSequence.valueAt (currentVolumeSequenceFrame)) / 15.0f;
        }
        else
        {
            switch (envelopePhase)
            {
                case kEnvelopePhaseA:
                    currentEnvelopeLevel += attack_slope;

                    if (currentEnvelopeLevel > 1.0)
                    {
                        currentEnvelopeLevel = 1.0;
                        envelopePhase = kEnvelopePhaseD;
                    }

                    break;

                case kEnvelopePhaseD:
                    currentEnvelopeLevel -= decay_slope;

                    if (currentEnvelopeLevel < sustain_level)
                    {
                        envelopePhase = kEnvelopePhaseS;
                        currentEnvelopeLevel = sustain_level;
                    }

                    break;

                case kEnvelopePhaseS:
                    currentEnvelopeLevel = sustain_level;
                    break;

                case kEnvelopePhaseR:
                    currentEnvelopeLevel -= release_slope;

                    if (currentEnvelopeLevel < 0)
                    {
                        currentEnvelopeLevel = 0;
                        clearCurrentNote();
                        angleDelta = 0.0;
                    }

                    break;
            }
        }

        //
        // Write to buffer
        //
        float currentSample = voltageForAngle (currentAngle) * currentEnvelopeLevel * ampByVelocityAndGain;

        for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
            outputBuffer.addSample (i, startSample, currentSample);

        //
        // Advance phase
        //
        calculateAngleDelta();

        currentAngle += angleDelta;

        while (currentAngle > 2.0 * MathConstants<float>::pi)
        {
            currentAngle -= 2.0 * MathConstants<float>::pi;
        }

        //
        // Advance control frame
        //
        controlFrameTimer += 1.0 / getSampleRate();

        if (controlFrameTimer >= controlFrameLength)
        {
            advanceControlFrame();

            while (controlFrameTimer >= controlFrameLength)
            {
                controlFrameTimer -= controlFrameLength;
            }
        }

        onFrameAdvanced();

        ++startSample;
    }
}

void BaseVoice::changeNote (int midiNoteNumber, float velocity) {
    noteNumber = midiNoteNumber;

    ampByVelocityAndGain = * (settingRefs->gain) * velocity; // velocity value range is 0.0f-1.0f
}


void BaseVoice::calculateAngleDelta()
{
    auto cyclesPerSecond = MidiMessage::getMidiNoteInHertz (noteNumber);
    auto cyclesPerSample = cyclesPerSecond / getSampleRate();

    angleDelta = cyclesPerSample * 2.0 * MathConstants<double>::pi;
}

void BaseVoice::advanceControlFrame()
{
    currentVolumeSequenceFrame = settingRefs->volumeSequence.nextIndexOf (currentVolumeSequenceFrame);

    if (currentVolumeSequenceFrame == FrameSequence::SHOULD_RETIRE)
    {
        currentEnvelopeLevel = 0;
        clearCurrentNote();
        angleDelta = 0.0;
    }
}
