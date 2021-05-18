/*
  ==============================================================================

    CustomSynth.cpp
    Created: 17 May 2021 11:29:59pm
    Author:  除村武志

  ==============================================================================
*/

#include "CustomSynth.h"
#include "BaseVoice.h"
#include "PluginProcessor.h"

CustomSynth::CustomSynth(Magical8bitPlug2AudioProcessor& p) : processor(p) {}

void CustomSynth::noteOn(int midiChannel, int midiNoteNumber, float velocity) {
    // Poly
    if (!processor.settingRefs.isMonophonic()) {
        Synthesiser::noteOn(midiChannel, midiNoteNumber, velocity);
        return;
    }
    
    // Mono
    auto voice = voices.getFirst();
    
    if (voice == nullptr) {
        return;
    }
    if (voice->isKeyDown()) {
        ((BaseVoice*)voice)->changeNote(midiNoteNumber, velocity);
    } else {
        Synthesiser::noteOn(midiChannel, midiNoteNumber, velocity);
    }
}

void CustomSynth::noteOff(int midiChannel, int midiNoteNumber, float velocity, bool allowTailOff) {
    Synthesiser::noteOff(midiChannel, midiNoteNumber, velocity, allowTailOff);
}

void CustomSynth::allNotesOff (const int midiChannel, const bool allowTailOff) {
    Synthesiser::allNotesOff(midiChannel, allowTailOff);
}

