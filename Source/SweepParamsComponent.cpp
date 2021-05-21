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

#include "SweepParamsComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
SweepParamsComponent::SweepParamsComponent (Magical8bitPlug2AudioProcessor& p)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    label.reset (new juce::Label ("label",
                                  TRANS("Auto Bend")));
    addAndMakeVisible (label.get());
    label->setFont (juce::Font (17.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    label->setJustificationType (juce::Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label->setBounds (0, 4, 150, 22);

    iniPitchSlider.reset (new SliderComponent (p, "sweepInitialPitch", "Ini.Pitch"));
    addAndMakeVisible (iniPitchSlider.get());
    iniPitchSlider->setName ("inital pitch slider");

    timeSlider.reset (new SliderComponent (p, "sweepTime", "Time"));
    addAndMakeVisible (timeSlider.get());
    timeSlider->setName ("time slider");


    //[UserPreSize]
    //[/UserPreSize]

    setSize (340, 86);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

SweepParamsComponent::~SweepParamsComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    label = nullptr;
    iniPitchSlider = nullptr;
    timeSlider = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void SweepParamsComponent::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void SweepParamsComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    iniPitchSlider->setBounds (0, 26, proportionOfWidth (1.0000f), 28);
    timeSlider->setBounds (0, 54, proportionOfWidth (1.0000f), 28);
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

<JUCER_COMPONENT documentType="Component" className="SweepParamsComponent" componentName=""
                 parentClasses="public Component" constructorParams="Magical8bitPlug2AudioProcessor&amp; p"
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="1" initialWidth="340" initialHeight="86">
  <BACKGROUND backgroundColour="ffffff"/>
  <LABEL name="label" id="bae3132bcad681ce" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="0 4 150 22" edTextCol="ff000000"
         edBkgCol="0" labelText="Auto Bend" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="17.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <GENERICCOMPONENT name="inital pitch slider" id="93ec1e79c45ddad4" memberName="iniPitchSlider"
                    virtualName="" explicitFocusOrder="0" pos="0 26 100% 28" class="SliderComponent"
                    params="p, &quot;sweepInitialPitch&quot;, &quot;Ini.Pitch&quot;"/>
  <GENERICCOMPONENT name="time slider" id="1be45518932375fc" memberName="timeSlider"
                    virtualName="" explicitFocusOrder="0" pos="0 54 100% 28" class="SliderComponent"
                    params="p, &quot;sweepTime&quot;, &quot;Time&quot;"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

