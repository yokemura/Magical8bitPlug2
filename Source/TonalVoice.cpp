/*
  ==============================================================================

    TonalVoice.cpp
    Created: 11 Nov 2019 9:36:34pm
    Author:  除村 武志

  ==============================================================================
*/

#include "TonalVoice.h"

//---------------------------------------------
//
// Tonal Voice
// The base for pulse/triangle (Abstract)
//
//---------------------------------------------
TonalVoice::TonalVoice (SettingRefs* sRefs) : BaseVoice (sRefs) {}

void TonalVoice::startNote (int midiNoteNumber, float velocity, SynthesiserSound*, int currentPitchBendPosition)
{
    BaseVoice::startNote (midiNoteNumber, velocity, 0, currentPitchBendPosition);

    currentBendAmount = * (settingRefs->bendRange) * ((double) (currentPitchBendPosition - 8192)) / 8192.0;
    currentPitchSequenceFrame = 0;
    vibratoCount = 0;

    float iniPitch = * (settingRefs->sweepInitialPitch);
    float time = * (settingRefs->sweepTime);
    currentAutoBendAmount = iniPitch;
    autoBendDelta = -1.0 * iniPitch / (time * getSampleRate());
}

void TonalVoice::advanceControlFrame()
{
    BaseVoice::advanceControlFrame();

    currentPitchSequenceFrame = settingRefs->pitchSequence.nextIndexOf (currentPitchSequenceFrame);
}

void TonalVoice::calculateAngleDelta()
{

    int noteNumberMod = 0;
    double finePitchInSeq = 0;

    if (settingRefs->isPitchSequenceEnabled())
    {
        switch (settingRefs->pitchSequenceMode())
        {
            case kPitchSequenceModeFine:
                finePitchInSeq = (double)settingRefs->pitchSequence.valueAt (currentPitchSequenceFrame) / 8.0;
                break;

            case kPitchSequenceModeCoarse:
                noteNumberMod = settingRefs->pitchSequence.valueAt (currentPitchSequenceFrame);
                break;

            default:
                break;
        }
    }

    double byWheel = settingRefs->vibratoIgnoresWheel() ? 1.0 : currentModWheelValue;
    double vibratoAmount = * (settingRefs->vibratoDepth) * sin (getVibratoPhase()) * byWheel;
    double noteNoInDouble = noteNumber
                            + noteNumberMod
                            + currentBendAmount
                            + currentAutoBendAmount
                            + vibratoAmount
                            + finePitchInSeq;

    auto cyclesPerSecond = noteNoToHeltzDouble (noteNoInDouble);
    auto cyclesPerSample = cyclesPerSecond / getSampleRate();

    angleDelta = cyclesPerSample * 2.0 * MathConstants<double>::pi;
}

void TonalVoice::pitchWheelMoved (int amount)
{
    currentBendAmount = * (settingRefs->bendRange) * ((double) (amount - 8192)) / 8192.0;
}

void TonalVoice::controllerMoved (int type, int amount)
{
    if (type == 1)  // Modulation
    {
        currentModWheelValue = (double)amount / 127.0;
    }
}

double TonalVoice::noteNoToHeltzDouble (double noteNoInDouble, const double frequencyOfA)
{
    return frequencyOfA * std::pow (2.0, (noteNoInDouble - 69) / 12.0);
}


double TonalVoice::getVibratoPhase()
{
    double sec = (double)vibratoCount / getSampleRate();

    float delay = * (settingRefs->vibratoDelay);
    float rate = * (settingRefs->vibratoRate);

    if ( sec < delay ) { return 0.0; }

    double phase = fmodf (( sec - delay ), rate) / rate * MathConstants<double>::twoPi;
    return phase;
}

void TonalVoice::onFrameAdvanced()
{
    vibratoCount++;

    currentAutoBendAmount = currentAutoBendAmount + autoBendDelta;

    if (autoBendDelta > 0)
    {
        // positive slope
        if (currentAutoBendAmount > 0)
        {
            currentAutoBendAmount = 0;
            autoBendDelta = 0;
        }
    }
    else
    {
        // negative slope
        if (currentAutoBendAmount < 0)
        {
            currentAutoBendAmount = 0;
            autoBendDelta = 0;
        }
    }
};
