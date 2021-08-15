/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
class AdvancedParamsComponent;
class PulseParamsComponent;
class BasicParamsComponent;
class EnvelopeParamsComponent;
class NoiseParamsComponent;
class BendParamsComponent;
class SweepParamsComponent;
class VibratoParamsComponent;
class WaveformParamsComponent;

//==============================================================================
/**
*/
class Magical8bitPlug2AudioProcessorEditor  : public AudioProcessorEditor
    , public AudioProcessorParameter::Listener
{
public:
    Magical8bitPlug2AudioProcessorEditor (Magical8bitPlug2AudioProcessor&);
    ~Magical8bitPlug2AudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void resizeWholePanel();
    void applyLookAndFeel();

    void parameterValueChanged (int parameterIndex, float newValue) override;
    void parameterGestureChanged (int parameterIndex, bool gestureIsStarting) override {};

    // waveform
    //void waveformInit();
    void waveformUpdate();

private:
    Magical8bitPlug2AudioProcessor& processor;

    std::unique_ptr<BasicParamsComponent> basicCompo;
    std::unique_ptr<EnvelopeParamsComponent> envCompo;
    std::unique_ptr<AdvancedParamsComponent> advCompo;
    std::unique_ptr<PulseParamsComponent> pulCompo;
    std::unique_ptr<NoiseParamsComponent> noiCompo;
    std::unique_ptr<BendParamsComponent> bendCompo;
    std::unique_ptr<SweepParamsComponent> sweepCompo;
    std::unique_ptr<VibratoParamsComponent> vibCompo;
    std::unique_ptr<WaveformParamsComponent> waveformCompo;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Magical8bitPlug2AudioProcessorEditor)
};
