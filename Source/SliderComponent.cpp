/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.5

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "SliderComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
SliderComponent::SliderComponent (Magical8bitPlug2AudioProcessor& p, String paramId, String name)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    label.reset (new Label ("label",
                            TRANS("Label")));
    addAndMakeVisible (label.get());
    label->setFont (Font (14.00f, Font::plain).withTypefaceStyle ("Regular"));
    label->setJustificationType (Justification::centredRight);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label->setBounds (8, 1, 60, 24);

    slider.reset (new Slider ("slider"));
    addAndMakeVisible (slider.get());
    slider->setRange (0, 10, 0.01);
    slider->setSliderStyle (Slider::LinearHorizontal);
    slider->setTextBoxStyle (Slider::TextBoxRight, false, 50, 20);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (360, 28);


    //[Constructor] You can add your own custom stuff here..
    label->setText (name, dontSendNotification);

    attc.reset (new SliderAttachment (p.parameters, paramId, *slider));
    //[/Constructor]
}

SliderComponent::~SliderComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    attc.reset();
    //[/Destructor_pre]

    label = nullptr;
    slider = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void SliderComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void SliderComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    slider->setBounds (72, 1, getWidth() - 80, 24);
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

<JUCER_COMPONENT documentType="Component" className="SliderComponent" componentName=""
                 parentClasses="public Component" constructorParams="Magical8bitPlug2AudioProcessor&amp; p, String paramId, String name"
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="1" initialWidth="360" initialHeight="28">
  <BACKGROUND backgroundColour="ffffff"/>
  <LABEL name="label" id="af1fa4a96c3448e5" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="8 1 60 24" edTextCol="ff000000" edBkgCol="0"
         labelText="Label" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="14.0"
         kerning="0.0" bold="0" italic="0" justification="34"/>
  <SLIDER name="slider" id="2d6901c46e73c1e" memberName="slider" virtualName=""
          explicitFocusOrder="0" pos="72 1 80M 24" min="0.0" max="10.0"
          int="0.01" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="50" textBoxHeight="20" skewFactor="1.0"
          needsCallback="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

