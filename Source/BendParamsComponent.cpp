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

#include "BendParamsComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
BendParamsComponent::BendParamsComponent (Magical8bitPlug2AudioProcessor& p)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    label.reset (new juce::Label ("label",
                                  TRANS("Bend Range")));
    addAndMakeVisible (label.get());
    label->setFont (juce::Font (17.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    label->setJustificationType (juce::Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label->setBounds (0, 4, 150, 22);

    sliderCompo.reset (new SliderComponent (p, "bendRange", "Range"));
    addAndMakeVisible (sliderCompo.get());
    sliderCompo->setName ("slider");


    //[UserPreSize]
    //[/UserPreSize]

    setSize (340, 58);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

BendParamsComponent::~BendParamsComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    label = nullptr;
    sliderCompo = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void BendParamsComponent::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void BendParamsComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    sliderCompo->setBounds (0, 26, proportionOfWidth (1.0000f), 28);
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

<JUCER_COMPONENT documentType="Component" className="BendParamsComponent" componentName=""
                 parentClasses="public Component" constructorParams="Magical8bitPlug2AudioProcessor&amp; p"
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="1" initialWidth="340" initialHeight="58">
  <BACKGROUND backgroundColour="ffffff"/>
  <LABEL name="label" id="bae3132bcad681ce" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="0 4 150 22" edTextCol="ff000000"
         edBkgCol="0" labelText="Bend Range" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="17.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <GENERICCOMPONENT name="slider" id="b01ddc412ec6dc27" memberName="sliderCompo"
                    virtualName="" explicitFocusOrder="0" pos="0 26 100% 28" class="SliderComponent"
                    params="p, &quot;bendRange&quot;, &quot;Range&quot;"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

