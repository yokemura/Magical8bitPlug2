/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.1.5

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "EnvelopeParamsComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
EnvelopeParamsComponent::EnvelopeParamsComponent (Magical8bitPlug2AudioProcessor& p)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    label.reset (new juce::Label ("label",
                                  TRANS("Envelope")));
    addAndMakeVisible (label.get());
    label->setFont (juce::Font (17.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    label->setJustificationType (juce::Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label->setBounds (0, 4, 150, 22);

    attackSlider.reset (new SliderComponent (p, "attack", "Attack"));
    addAndMakeVisible (attackSlider.get());
    attackSlider->setName ("attack slider");

    decaySlider.reset (new SliderComponent (p, "decay", "Decay"));
    addAndMakeVisible (decaySlider.get());
    decaySlider->setName ("decay slider");

    sustainSlider.reset (new SliderComponent (p, "suslevel", "Sustain"));
    addAndMakeVisible (sustainSlider.get());
    sustainSlider->setName ("sustain slider");

    releaseSlider.reset (new SliderComponent (p, "release", "Release"));
    addAndMakeVisible (releaseSlider.get());
    releaseSlider->setName ("release slider");

    warningLabel.reset (new juce::Label ("warning label",
                                         juce::String()));
    addAndMakeVisible (warningLabel.get());
    warningLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    warningLabel->setJustificationType (juce::Justification::centredRight);
    warningLabel->setEditable (false, false, false);
    warningLabel->setColour (juce::Label::textColourId, juce::Colour (0xffe22be0));
    warningLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    warningLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (340, 142);


    //[Constructor] You can add your own custom stuff here..
    ColorScheme cs = ColorScheme (p.settingRefs.colorSchemeType());
    warningLabelLookAndFeel.setColour (Label::textColourId, cs.warning);
    warningLabel->setLookAndFeel (&warningLabelLookAndFeel);
    //[/Constructor]
}

EnvelopeParamsComponent::~EnvelopeParamsComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    label = nullptr;
    attackSlider = nullptr;
    decaySlider = nullptr;
    sustainSlider = nullptr;
    releaseSlider = nullptr;
    warningLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void EnvelopeParamsComponent::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void EnvelopeParamsComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    attackSlider->setBounds (0, 26, proportionOfWidth (1.0000f), 28);
    decaySlider->setBounds (0, 54, proportionOfWidth (1.0000f), 28);
    sustainSlider->setBounds (0, 82, proportionOfWidth (1.0000f), 28);
    releaseSlider->setBounds (0, 110, proportionOfWidth (1.0000f), 28);
    warningLabel->setBounds (getWidth() - 8 - 246, 4, 246, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void EnvelopeParamsComponent::enablementChanged()
{
    //[UserCode_enablementChanged] -- Add your code here...
    if (isEnabled())
    {
        warningLabel->setText (TRANS (""), dontSendNotification);
    }
    else
    {
        warningLabel->setText (TRANS ("Overridden by Custom Envelope"), dontSendNotification);
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

<JUCER_COMPONENT documentType="Component" className="EnvelopeParamsComponent"
                 componentName="" parentClasses="public Component" constructorParams="Magical8bitPlug2AudioProcessor&amp; p"
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="1" initialWidth="340" initialHeight="142">
  <METHODS>
    <METHOD name="enablementChanged()"/>
  </METHODS>
  <BACKGROUND backgroundColour="ffffff"/>
  <LABEL name="label" id="bae3132bcad681ce" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="0 4 150 22" edTextCol="ff000000"
         edBkgCol="0" labelText="Envelope" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="17.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <GENERICCOMPONENT name="attack slider" id="93ec1e79c45ddad4" memberName="attackSlider"
                    virtualName="" explicitFocusOrder="0" pos="0 26 100% 28" class="SliderComponent"
                    params="p, &quot;attack&quot;, &quot;Attack&quot;"/>
  <GENERICCOMPONENT name="decay slider" id="1be45518932375fc" memberName="decaySlider"
                    virtualName="" explicitFocusOrder="0" pos="0 54 100% 28" class="SliderComponent"
                    params="p, &quot;decay&quot;, &quot;Decay&quot;"/>
  <GENERICCOMPONENT name="sustain slider" id="5c2169fddb4cc33" memberName="sustainSlider"
                    virtualName="" explicitFocusOrder="0" pos="0 82 100% 28" class="SliderComponent"
                    params="p, &quot;suslevel&quot;, &quot;Sustain&quot;"/>
  <GENERICCOMPONENT name="release slider" id="9d35239102eeb521" memberName="releaseSlider"
                    virtualName="" explicitFocusOrder="0" pos="0 110 100% 28" class="SliderComponent"
                    params="p, &quot;release&quot;, &quot;Release&quot;"/>
  <LABEL name="warning label" id="624aa3e1415981e3" memberName="warningLabel"
         virtualName="" explicitFocusOrder="0" pos="8Rr 4 246 24" textCol="ffe22be0"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="34"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

