/*
  ==============================================================================

    CustomSynth.h
    Created: 17 May 2021 11:29:59pm
    Author:  除村武志

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class Magical8bitPlug2AudioProcessor;
class TonalVoice;

class CustomSynth : public Synthesiser {
public:
    CustomSynth(Magical8bitPlug2AudioProcessor& p);
    
    void noteOn(int midiChannel, int midiNoteNumber, float velocity) override;
    void noteOff(int midiChannel, int midiNoteNumber, float velocity, bool allowTailOff) override;
    void allNotesOff (const int midiChannel, const bool allowTailOff) override;
    
private:
    TonalVoice* getVoiceIfShouldProcessInMonoMode();
    Magical8bitPlug2AudioProcessor& processor;
};
