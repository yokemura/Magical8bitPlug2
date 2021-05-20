/*
  ==============================================================================

    CustomSynth.cpp
    Created: 17 May 2021 11:29:59pm
    Author:  除村武志

  ==============================================================================
*/

#include "CustomSynth.h"
#include "BaseVoice.h"
#include "TonalVoice.h"
#include "PluginProcessor.h"

CustomSynth::CustomSynth(Magical8bitPlug2AudioProcessor& p) : processor(p) {}

TonalVoice* CustomSynth::getVoiceIfShouldProcessInMonoMode() {
    if (!processor.settingRefs.isMonophonic()) {
        return nullptr;
    }
    if (processor.settingRefs.monophonicBehavior() == kNonLegato) {
        return nullptr;
    }
    
    // Try casting into TonalVoice* and return it if success(otherwise returns nullptr)
    return dynamic_cast<TonalVoice *>(voices.getFirst());
}

void CustomSynth::noteOn(int midiChannel, int midiNoteNumber, float velocity) {
    TonalVoice *voice = getVoiceIfShouldProcessInMonoMode();
    
    if (voice == nullptr) {
        Synthesiser::noteOn(midiChannel, midiNoteNumber, velocity);
        return;
    }
    
    // Mono
    
    // Start thread guard
    const ScopedLock sl (lock);

    if (voice->isKeyDown()) {
        // Already key on
        switch (processor.settingRefs.monophonicBehavior()) {
            case kLegato:
                voice->addLegatoNote(midiNoteNumber, velocity);
                break;
            case kArpeggioUp:
                voice->addArpeggioNoteAscending(midiNoteNumber);
                break;
            case kArpeggioDown:
                voice->addArpeggioNoteDescending(midiNoteNumber);
                break;
            default:
                // no-op
                break;
        }
    } else {
        switch (processor.settingRefs.monophonicBehavior()) {
            case kLegato:
                // just start
                Synthesiser::noteOn(midiChannel, midiNoteNumber, velocity);
                voice->setLegatoMode(*(processor.settingRefs.portamentoTime));
                break;
            case kArpeggioUp:
            case kArpeggioDown:
                // calc arpeggio interval
                // set arpeggio mode with this note number and arp interval
                break;
            default:
                // no-op
                break;
        }
    }
}

void CustomSynth::noteOff(int midiChannel, int midiNoteNumber, float velocity, bool allowTailOff) {
    TonalVoice *voice = getVoiceIfShouldProcessInMonoMode();
    
    if (voice == nullptr) {
        Synthesiser::noteOff(midiChannel, midiNoteNumber, velocity, allowTailOff);
        return;
    }
    
    // mono
    
    // Start thread guard
    const ScopedLock sl (lock);

    if (!voice->isKeyDown()) {
        // key is already off
        return;
    }
    
    switch (processor.settingRefs.monophonicBehavior()) {
        case kLegato:
        {
            int numBuffer = voice->removeLegatoNote(midiNoteNumber);
            if (numBuffer < 1) {
                Synthesiser::noteOff(midiChannel, voice->getCurrentlyPlayingNote(), velocity, allowTailOff);
            }
        }
            break;
        case kArpeggioUp:
        case kArpeggioDown:
            // remove arpeggio note and get # of remaining arpeggio notes
            // if zero
            //   all notes off
            break;
        default:
            break;
    }
}

void CustomSynth::allNotesOff (const int midiChannel, const bool allowTailOff) {
    Synthesiser::allNotesOff(midiChannel, allowTailOff);
}

