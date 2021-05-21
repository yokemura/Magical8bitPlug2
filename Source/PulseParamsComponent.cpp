/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.0.8

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "PulseParamsComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
PulseParamsComponent::PulseParamsComponent (Magical8bitPlug2AudioProcessor& p)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    label.reset (new juce::Label ("label",
                                  TRANS("Pulse")));
    addAndMakeVisible (label.get());
    label->setFont (juce::Font (17.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    label->setJustificationType (juce::Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label->setBounds (0, 4, 150, 22);

    dutySelector.reset (new ChoiceComponent (p, "duty", "Duty"));
    addAndMakeVisible (dutySelector.get());
    dutySelector->setName ("duty selector");

    warningLabel.reset (new juce::Label ("warning label",
                                         juce::String()));
    addAndMakeVisible (warningLabel.get());
    warningLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    warningLabel->setJustificationType (juce::Justification::centredRight);
    warningLabel->setEditable (false, false, false);
    warningLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    warningLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (340, 58);


    //[Constructor] You can add your own custom stuff here..
    ColorScheme cs = ColorScheme (p.settingRefs.colorSchemeType());
    warningLabelLookAndFeel.setColour (Label::textColourId, cs.warning);
    warningLabel->setLookAndFeel (&warningLabelLookAndFeel);
    //[/Constructor]
}

PulseParamsComponent::~PulseParamsComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    label = nullptr;
    dutySelector = nullptr;
    warningLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PulseParamsComponent::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void PulseParamsComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    dutySelector->setBounds (0, 26, proportionOfWidth (1.0000f), 28);
    warningLabel->setBounds (getWidth() - 8 - 246, 4, 246, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void PulseParamsComponent::enablementChanged()
{
    //[UserCode_enablementChanged] -- Add your code here...
    if (isEnabled())
    {
        warningLabel->setText (TRANS (""), dontSendNotification);
    }
    else
    {
        warningLabel->setText (TRANS ("Overridden by Duty Envelope"), dontSendNotification);
    }

    //[/UserCode_enablementChanged]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PulseParamsComponent" componentName=""
                 parentClasses="public Component" constructorParams="Magical8bitPlug2AudioProcessor&amp; p"
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="1" initialWidth="340" initialHeight="58">
  <METHODS>
    <METHOD name="enablementChanged()"/>
  </METHODS>
  <BACKGROUND backgroundColour="ffffff"/>
  <LABEL name="label" id="bae3132bcad681ce" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="0 4 150 22" edTextCol="ff000000"
         edBkgCol="0" labelText="Pulse" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="17.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <GENERICCOMPONENT name="duty selector" id="b01ddc412ec6dc27" memberName="dutySelector"
                    virtualName="" explicitFocusOrder="0" pos="0 26 100% 28" class="ChoiceComponent"
                    params="p, &quot;duty&quot;, &quot;Duty&quot;"/>
  <LABEL name="warning label" id="624aa3e1415981e3" memberName="warningLabel"
         virtualName="" explicitFocusOrder="0" pos="8Rr 4 246 24" edTextCol="ff000000"
         edBkgCol="0" labelText="" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="34"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

