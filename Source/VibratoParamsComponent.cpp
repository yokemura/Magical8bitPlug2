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

#include "VibratoParamsComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
VibratoParamsComponent::VibratoParamsComponent (Magical8bitPlug2AudioProcessor& p)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    label.reset (new juce::Label ("label",
                                  TRANS("Vibrato")));
    addAndMakeVisible (label.get());
    label->setFont (juce::Font (17.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    label->setJustificationType (juce::Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label->setBounds (0, 4, 150, 22);

    ratioSlider.reset (new SliderComponent (p, "vibratoRate", "Cycle Len."));
    addAndMakeVisible (ratioSlider.get());
    ratioSlider->setName ("ratio slider");

    depthSlider.reset (new SliderComponent (p, "vibratoDepth", "Depth"));
    addAndMakeVisible (depthSlider.get());
    depthSlider->setName ("depth slider");

    delaySlider.reset (new SliderComponent (p, "vibratoDelay", "Delay"));
    addAndMakeVisible (delaySlider.get());
    delaySlider->setName ("delay slider");

    ignoreWheelSwitch.reset (new CheckBoxComponent (p, "vibratoIgnoresWheel_raw", "Ignores Wheel"));
    addAndMakeVisible (ignoreWheelSwitch.get());
    ignoreWheelSwitch->setName ("ignore wheel switch");


    //[UserPreSize]
    //[/UserPreSize]

    setSize (340, 142);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

VibratoParamsComponent::~VibratoParamsComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    label = nullptr;
    ratioSlider = nullptr;
    depthSlider = nullptr;
    delaySlider = nullptr;
    ignoreWheelSwitch = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void VibratoParamsComponent::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void VibratoParamsComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    ratioSlider->setBounds (0, 26, proportionOfWidth (1.0000f), 28);
    depthSlider->setBounds (0, 54, proportionOfWidth (1.0000f), 28);
    delaySlider->setBounds (0, 82, proportionOfWidth (1.0000f), 28);
    ignoreWheelSwitch->setBounds (0, 110, proportionOfWidth (1.0000f), 28);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="VibratoParamsComponent" componentName=""
                 parentClasses="public Component" constructorParams="Magical8bitPlug2AudioProcessor&amp; p"
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="1" initialWidth="340" initialHeight="142">
  <BACKGROUND backgroundColour="ffffff"/>
  <LABEL name="label" id="bae3132bcad681ce" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="0 4 150 22" edTextCol="ff000000"
         edBkgCol="0" labelText="Vibrato" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="17.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <GENERICCOMPONENT name="ratio slider" id="93ec1e79c45ddad4" memberName="ratioSlider"
                    virtualName="" explicitFocusOrder="0" pos="0 26 100% 28" class="SliderComponent"
                    params="p, &quot;vibratoRate&quot;, &quot;Cycle Len.&quot;"/>
  <GENERICCOMPONENT name="depth slider" id="1be45518932375fc" memberName="depthSlider"
                    virtualName="" explicitFocusOrder="0" pos="0 54 100% 28" class="SliderComponent"
                    params="p, &quot;vibratoDepth&quot;, &quot;Depth&quot;"/>
  <GENERICCOMPONENT name="delay slider" id="5c2169fddb4cc33" memberName="delaySlider"
                    virtualName="" explicitFocusOrder="0" pos="0 82 100% 28" class="SliderComponent"
                    params="p, &quot;vibratoDelay&quot;, &quot;Delay&quot;"/>
  <GENERICCOMPONENT name="ignore wheel switch" id="9d35239102eeb521" memberName="ignoreWheelSwitch"
                    virtualName="" explicitFocusOrder="0" pos="0 110 100% 28" class="CheckBoxComponent"
                    params="p, &quot;vibratoIgnoresWheel_raw&quot;, &quot;Ignores Wheel&quot;"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

