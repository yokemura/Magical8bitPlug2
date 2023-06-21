/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "AdvancedParamsComponent.h"
#include "MonophonicComponent.h"
#include "PulseParamsComponent.h"
#include "BasicParamsComponent.h"
#include "EnvelopeParamsComponent.h"
#include "NoiseParamsComponent.h"
#include "BendParamsComponent.h"
#include "SweepParamsComponent.h"
#include "VibratoParamsComponent.h"

//==============================================================================
Magical8bitPlug2AudioProcessorEditor::Magical8bitPlug2AudioProcessorEditor (Magical8bitPlug2AudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    isComponentsReady = false;
    
    applyLookAndFeel();

    basicCompo.reset (new BasicParamsComponent (p, *this));
    addAndMakeVisible (basicCompo.get());
    
    monoCompo.reset (new MonophonicComponent (p));
    addAndMakeVisible(monoCompo.get());

    envCompo.reset (new EnvelopeParamsComponent (p));
    addAndMakeVisible (envCompo.get());

    advCompo.reset (new AdvancedParamsComponent (p));
    addAndMakeVisible (advCompo.get());

    pulCompo.reset (new PulseParamsComponent (p));
    addAndMakeVisible (pulCompo.get());

    noiCompo.reset (new NoiseParamsComponent (p));
    addAndMakeVisible (noiCompo.get());

    bendCompo.reset (new BendParamsComponent (p));
    addAndMakeVisible (bendCompo.get());

    sweepCompo.reset (new SweepParamsComponent (p));
    addAndMakeVisible (sweepCompo.get());

    vibCompo.reset (new VibratoParamsComponent (p));
    addAndMakeVisible (vibCompo.get());

    (p.parameters.getParameter ("isVolumeSequenceEnabled_raw"))->addListener (this);
    (p.parameters.getParameter ("isDutySequenceEnabled_raw"))->addListener (this);

    isComponentsReady = true;
    resizeWholePanel();
}

void Magical8bitPlug2AudioProcessorEditor::applyLookAndFeel()
{
    ColorScheme cs = ColorScheme (processor.settingRefs.colorSchemeType());

    //
    // Slider
    //
    getLookAndFeel().setColour (Slider::trackColourId, cs.main);
    getLookAndFeel().setColour (Slider::thumbColourId, cs.accent);
    getLookAndFeel().setColour (Slider::backgroundColourId, cs.mainDarkened);
    getLookAndFeel().setColour (Slider::textBoxTextColourId, cs.mainThinLine);
    getLookAndFeel().setColour (Slider::textBoxBackgroundColourId, cs.textBoxFill);
    getLookAndFeel().setColour (Slider::textBoxHighlightColourId, cs.mainThinLine);
    getLookAndFeel().setColour (Slider::textBoxOutlineColourId, cs.genericBorder);

    getLookAndFeel().setColour (TextButton::ColourIds::buttonColourId, cs.boxFill);
    getLookAndFeel().setColour (TextButton::ColourIds::textColourOffId, cs.reversedForeground);
    getLookAndFeel().setColour (Label::textWhenEditingColourId, cs.mainThinLine);

    //
    // Label
    //
    getLookAndFeel().setColour (Label::textColourId, cs.mainThinLine);

    //
    // Toggle Button
    //
    getLookAndFeel().setColour (ToggleButton::textColourId, cs.mainThinLine);
    getLookAndFeel().setColour (ToggleButton::tickDisabledColourId, cs.mainThinLine);
    getLookAndFeel().setColour (ToggleButton::tickColourId, cs.mainThinLine);

    //
    // Text Editor
    //
    getLookAndFeel().setColour (TextEditor::textColourId, cs.mainThinLine);
    getLookAndFeel().setColour (TextEditor::backgroundColourId, cs.textBoxFill);
    getLookAndFeel().setColour (TextEditor::outlineColourId, cs.genericBorder);

    //
    // Combo Box
    //
    getLookAndFeel().setColour (ComboBox::backgroundColourId, cs.boxFill);
    getLookAndFeel().setColour (ComboBox::textColourId, cs.reversedForeground);
    getLookAndFeel().setColour (ComboBox::arrowColourId, cs.reversedForeground);
    getLookAndFeel().setColour (ComboBox::buttonColourId, cs.mainThinLine);
    getLookAndFeel().setColour (ComboBox::outlineColourId, cs.genericBorder);
}

Magical8bitPlug2AudioProcessorEditor::~Magical8bitPlug2AudioProcessorEditor()
{
    (processor.parameters.getParameter ("isVolumeSequenceEnabled_raw"))->removeListener (this);
    (processor.parameters.getParameter ("isDutySequenceEnabled_raw"))->removeListener (this);
}

//==============================================================================
struct
{
    const int totalWidth = 640;
    const int topMargin = 10;
    const int leftMargin = 10;
    const int bottomMargin = 20;
    const int halfComponentWidth = 300;
    const int fullComponentWidth = 620;
    const int sectionSeparatorHeight = 16;
    const int verticalSeparatorWidth = 16;
    const int componentMargin = 2;
    const int indexHeight = 22;
    const int genericControlHeight = 28;
    const int customEnvelopeHeight =  56;

    const int basCompoHeight = componentMargin * 2
                               + genericControlHeight * 2;
    const int monoCompoHeight = componentMargin * 2
                                + indexHeight
                                + customEnvelopeHeight;
    const int toneSpecificControlHeight = componentMargin * 2
                                          + indexHeight
                                          + genericControlHeight;
    const int envCompoHeight = componentMargin * 2
                               + indexHeight
                               + genericControlHeight * 4;
    const int bendCompoHeight = componentMargin * 2
                                + indexHeight
                                + genericControlHeight;
    const int sweepCompoHeight = componentMargin * 2
                                 + indexHeight
                                 + genericControlHeight * 2;
    const int vibCompoHeight = componentMargin * 2
                               + indexHeight
                               + genericControlHeight * 4;
    const int advCompoHeight = componentMargin * 2
                               + indexHeight
                               + customEnvelopeHeight * 4;
    const int totalHeight (bool isAdvOptOn, bool isMono)
    {
        int retHeight = topMargin
                      + basCompoHeight
                      + sectionSeparatorHeight
                      + toneSpecificControlHeight
                      + envCompoHeight
                      + bendCompoHeight
                      + bottomMargin;
        if (isAdvOptOn)
        {
            retHeight += sectionSeparatorHeight
                         + advCompoHeight;
        }
        if (isMono)
        {
            retHeight += monoCompoHeight;
        }
        return retHeight;
    }
} sizes;

void Magical8bitPlug2AudioProcessorEditor::paint (Graphics& g)
{
    // fill the whole window white
    ColorScheme cs = ColorScheme (processor.settingRefs.colorSchemeType());
    g.fillAll (cs.background);

    int y = sizes.topMargin
            + sizes.basCompoHeight
            + sizes.sectionSeparatorHeight / 2;
    g.setColour (cs.genericBorder);

    Line<float> line (Point<float> (sizes.leftMargin, y),
                      Point<float> (sizes.leftMargin + sizes.fullComponentWidth, y));

    g.drawLine (line, 1.0f);
}


void Magical8bitPlug2AudioProcessorEditor::resized()
{
    applyLookAndFeel();

    //
    // Header
    //
    int x = sizes.leftMargin;
    int y = sizes.topMargin;
    int w = sizes.halfComponentWidth;
    basicCompo->setBounds (x, y, sizes.fullComponentWidth, sizes.basCompoHeight);
    
    y += sizes.basCompoHeight + sizes.sectionSeparatorHeight;
    
    //
    // Monophonic
    //
    if (processor.settingRefs.isMonophonic()) {
        monoCompo->setBounds(x, y, sizes.fullComponentWidth, sizes.monoCompoHeight);
        y += sizes.monoCompoHeight;
    }
    
    int y1 = y;
    int y2 = y;

    //
    // Main part - Left
    //

    pulCompo->setBounds (x, y1, w, sizes.toneSpecificControlHeight);
    noiCompo->setBounds (x, y1, w, sizes.toneSpecificControlHeight);
    y1 += sizes.toneSpecificControlHeight;

    envCompo->setBounds (x, y1, w, sizes.envCompoHeight);
    y1 += sizes.envCompoHeight;

    bendCompo->setBounds (x, y1, w, sizes.bendCompoHeight);
    y1 += sizes.bendCompoHeight;

    //
    // Main part - Right
    //
    x = sizes.leftMargin + sizes.halfComponentWidth + sizes.verticalSeparatorWidth;

    sweepCompo->setBounds (x, y2, w, sizes.sweepCompoHeight);
    y2 += sizes.sweepCompoHeight;

    vibCompo->setBounds (x, y2, w, sizes.vibCompoHeight);
    y2 += sizes.vibCompoHeight;

    //
    // Advanced part
    //
    x = sizes.leftMargin;
    int y3 = y1 > y2 ? y1 : y2;
    y3 += sizes.sectionSeparatorHeight;
    advCompo->setBounds (x, y3, sizes.fullComponentWidth, sizes.advCompoHeight);

    //
    // Visibility
    //
    switch (processor.settingRefs.oscillatorType())
    {
        case kVoiceTypePulse:
            pulCompo->setVisible (true);
            noiCompo->setVisible (false);
            break;

        case kVoiceTypeNoise:
            pulCompo->setVisible (false);
            noiCompo->setVisible (true);
            break;

        default:
            pulCompo->setVisible (false);
            noiCompo->setVisible (false);
            break;
    }
    
    monoCompo->setVisible(processor.settingRefs.isMonophonic());

    //
    // Enable/Disable
    //
    envCompo->setEnabled (!processor.settingRefs.isVolumeSequenceEnabled());
    pulCompo->setEnabled (!processor.settingRefs.isDutySequenceEnabled());

    sendLookAndFeelChange();
}

void Magical8bitPlug2AudioProcessorEditor::resizeWholePanel()
{
    if (!isComponentsReady) {
        return;
    }
    setSize (sizes.totalWidth, sizes.totalHeight (processor.settingRefs.isAdvancedPanelOpen(), processor.settingRefs.isMonophonic()));
}

void Magical8bitPlug2AudioProcessorEditor::parameterValueChanged (int parameterIndex, float newValue)
{
    if (parameterIndex == (processor.parameters.getParameter ("isVolumeSequenceEnabled_raw"))->getParameterIndex())
    {
        printf ("Volume sequence enabled flag %f\n", newValue);
        bool isEnabled = newValue > 0.5;
        envCompo->setEnabled (!isEnabled);
    }
    else if (parameterIndex == (processor.parameters.getParameter ("isDutySequenceEnabled_raw"))->getParameterIndex())
    {
        printf ("Duty sequence enabled flag %f\n", newValue);
        bool isEnabled = newValue > 0.5;
        pulCompo->setEnabled (!isEnabled);
    }
}

