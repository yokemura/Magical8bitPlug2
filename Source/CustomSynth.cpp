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
                // start note and set legato mode
                Synthesiser::noteOn(midiChannel, midiNoteNumber, velocity);
                voice->setLegatoMode(*(processor.settingRefs.portamentoTime));
                break;
            case kArpeggioUp:
            case kArpeggioDown:
                // start note and calc arpeggio interval
                Synthesiser::noteOn(midiChannel, midiNoteNumber, velocity);
                voice->setArpeggioMode(calcArpeggioInterval());
                break;
            default:
                // no-op
                break;
        }
    }
}

double CustomSynth::calcArpeggioInterval() {
    switch (processor.settingRefs.apreggioIntervalType()) {
        case k1frame:
            return 1.0 / 60.0;
        case k2frames:
            return 1.0 / 30.0;
        case k3frames:
            return 1.0 / 20.0;
        case k64th:
            return 240.0 / (processor.getCurrentBPM() * 64);
        case k48th:
            return 240.0 / (processor.getCurrentBPM() * 48);
        case k32nd:
            return 240.0 / (processor.getCurrentBPM() * 32);
        case k24th:
            return 240.0 / (processor.getCurrentBPM() * 24);
        case kSlider:
            return *(processor.settingRefs.arpeggioIntervalSliderValue);
        default:
            return 1.0 / 60.0;
            break;
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
        {
            int numBuffer = voice->removeArpeggioNote(midiNoteNumber);
            if (numBuffer < 1) {
                Synthesiser::noteOff(midiChannel, voice->getCurrentlyPlayingNote(), velocity, allowTailOff);
            }
        }
            break;
        default:
            break;
    }
}

void CustomSynth::allNotesOff (const int midiChannel, const bool allowTailOff) {
    Synthesiser::allNotesOff(midiChannel, allowTailOff);
}

