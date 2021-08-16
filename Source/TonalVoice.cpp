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
    currentNumRetireBuffer = 0;
    for (int i=0; i<10; i++) { retireBuffer[i] = 0; }
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


void TonalVoice::setLegatoMode(double time, int midiCh) {
    portamentoTime = time;
    primaryMidiChannel = midiCh;
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


void TonalVoice::setArpeggioMode(double interval, int midiCh)
{
    arpeggioFrameLength = interval;
    arpeggioFrameTimer = 0;
    currentArpeggioFrame = 0;
    currentNumNoteBuffer = 1;
    noteBuffer[0] = noteNumber;
    primaryMidiChannel = midiCh;
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
    
    // Just push the note number to Retire Buffer
    retireBuffer[currentNumRetireBuffer] = midiNoteNumber;
    currentNumRetireBuffer++;
   
    // Observed like current number of notes already decreased
    return currentNumNoteBuffer - currentNumRetireBuffer;
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
    
    if (arpeggioFrameLength > 0) { // Arpeggio mode is on
        arpeggioFrameTimer += 1.0 / getSampleRate();
        
        if (arpeggioFrameTimer >= arpeggioFrameLength)
        { // Arpeggio phase advances
            if (!isInReleasePhase()) {
                // Process the retirements first
                for(int j = 0; j<currentNumRetireBuffer; j++) {
                    int target = retireBuffer[j];
                    int i = 0;
                    
                    // Find first match
                    for (i=0; i<currentNumNoteBuffer; i++) {
                        if (noteBuffer[i] == target) break;
                    }
                    if (i == currentNumNoteBuffer) { // not found
                        continue;
                    }
                    shiftNoteBuffer(i);
                    currentNumNoteBuffer--;
                }
                
                // Clear Retire Buffer
                currentNumRetireBuffer = 0;
                for (int i=0; i<10; i++) { retireBuffer[i] = 0; }
            } /* else {
               Retirements should not happen in Release Phase
               to keep the arpeggio playing during the release.
            } */
            
            if (noteBuffer[currentArpeggioFrame] == noteNumber || noteBuffer[currentArpeggioFrame] == 0) {
                // Normally 'currentArpaggioFrame' will be updated every frame with
                // 'noteBuffer[currentArpeggioFrame] == noteNumber' condition,
                // but when the retirement happens currentArpeggioFrame may point at the slot already gone.
                // to handle this situation the condition 'noteBuffer[currentArpeggioFrame] == 0' is added.
                
                currentArpeggioFrame++;

                if (currentArpeggioFrame >= currentNumNoteBuffer) {
                    currentArpeggioFrame = 0;
                }
            } /* else {
               In cases like retirement happens, or new arpeggio note is added
               the note at currentArpeggioFrame is no longer the same,
               so currentArpeggioFrame doesn't have to be updated.
               Moreover, updating currentArpeggioFrame in this case
               often results in sounding the same note over two frames.
            } */
            
            noteNumber = noteBuffer[currentArpeggioFrame];

            while (arpeggioFrameTimer >= arpeggioFrameLength)
            {
                arpeggioFrameTimer -= arpeggioFrameLength;
            }
        }
    }
    
    
};

bool TonalVoice::isInReleasePhase() {
    if (settingRefs->isVolumeSequenceEnabled()) {
        return settingRefs->volumeSequence.isInRelease(currentVolumeSequenceFrame);
    } else {
        return envelopePhase == kEnvelopePhaseR;
    }
}
