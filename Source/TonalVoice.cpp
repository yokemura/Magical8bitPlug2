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
    
    portamentoTime = 0;
    currentArpeggioFrame = 0;
    arpeggioFrameTimer = 0;
    arpeggioFrameLength = 0;
    currentNumNoteBuffer = 0;
    for (int i=0; i<10; i++) { noteBuffer[i] = 0; }
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


void TonalVoice::setLegatoMode(double time) {
    portamentoTime = time;
}

// The interface says "add" but the implementation is just using the latest value.
// It is because the original intension was to keep all the pressing keys and choose the apropriate one with certain algorithm
void TonalVoice::addLegatoNote (int midiNoteNumber, float velocity) {
    if (currentNumNoteBuffer >= 10) {
        return;
    }
    
    int previousNoteNo = noteNumber;
    BaseVoice::changeNote(midiNoteNumber, velocity);
    
    // Portamento implementation is just applying auto bend
    if (portamentoTime > 0) {
        currentAutoBendAmount = (double)(previousNoteNo - midiNoteNumber);
        autoBendDelta = -1.0 * currentAutoBendAmount / (portamentoTime * getSampleRate());
    }
}

int TonalVoice::removeLegatoNote(int midiNoteNumber) {
    if (midiNoteNumber == noteNumber) {
        return 0;
    } else {
        return 1;
    }
}


void TonalVoice::setArpeggioMode(double interval)
{
    arpeggioFrameLength = interval;
    arpeggioFrameTimer = 0;
    currentArpeggioFrame = 0;
    currentNumNoteBuffer = 1;
    noteBuffer[0] = noteNumber;
}

void TonalVoice::addArpeggioNoteAscending(int midiNoteNumber)
{
    if (currentNumNoteBuffer >= 10) {
        return;
    }
    int i;
    for (i = 0; i<currentNumNoteBuffer; i++) {
        if (noteBuffer[i] > midiNoteNumber) break;
    }
    
    pushNoteBuffer(i, midiNoteNumber);
    
    currentNumNoteBuffer++;
}

void TonalVoice::addArpeggioNoteDescending(int midiNoteNumber)
{
    if (currentNumNoteBuffer >= 10) {
        return;
    }
    int i;
    for (i = 0; i<currentNumNoteBuffer; i++) {
        if (noteBuffer[i] < midiNoteNumber) break;
    }
    
    pushNoteBuffer(i, midiNoteNumber);
    
    currentNumNoteBuffer++;
}

/// Returns number of remaining arpeggio notes
int TonalVoice::removeArpeggioNote(int midiNoteNumber)
{
    if (currentNumNoteBuffer==0) {
        return 0;
    }
    
    int i;
    for (i=0; i<currentNumNoteBuffer; i++) {
        if (noteBuffer[i] == midiNoteNumber) break;
    }
    if (i == currentNumNoteBuffer) { // not found
        return currentNumNoteBuffer;
    }
    shiftNoteBuffer(i);
    currentNumNoteBuffer--;
    
    return currentNumNoteBuffer;
}

void TonalVoice::pushNoteBuffer(int index, int value) {
    for (int i=9; i>index; i--) {
        noteBuffer[i] = noteBuffer[i-1];
    }
    noteBuffer[index] = value;
}

void TonalVoice::shiftNoteBuffer(int index) {
    for (int i=index; i<9; i++) {
        noteBuffer[i] = noteBuffer[i+1];
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
    
    if (arpeggioFrameLength > 0) {
        arpeggioFrameTimer += 1.0 / getSampleRate();
        
        if (arpeggioFrameTimer >= arpeggioFrameLength)
        {
            currentArpeggioFrame++;

            if (currentArpeggioFrame >= currentNumNoteBuffer) {
                currentArpeggioFrame = 0;
            }
            noteNumber = noteBuffer[currentArpeggioFrame];

            while (arpeggioFrameTimer >= arpeggioFrameLength)
            {
                arpeggioFrameTimer -= arpeggioFrameLength;
            }
        }
    }
};
