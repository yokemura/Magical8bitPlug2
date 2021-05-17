/*
  ==============================================================================

    CustomSynth.cpp
    Created: 17 May 2021 11:29:59pm
    Author:  除村武志

  ==============================================================================
*/

#include "CustomSynth.h"

CustomSynth::CustomSynth(Magical8bitPlug2AudioProcessor& p) : processor(p) {}

void CustomSynth::noteOn(int midiChannel, int midiNoteNumber, float velocity) {
    Synthesiser::noteOn(midiChannel, midiNoteNumber, velocity);
}

void CustomSynth::noteOff(int midiChannel, int midiNoteNumber, float velocity, bool allowTailOff) {
    Synthesiser::noteOff(midiChannel, midiNoteNumber, velocity, allowTailOff);
}
