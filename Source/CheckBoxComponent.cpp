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
#include "PluginProcessor.h"
//[/Headers]

#include "CheckBoxComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
CheckBoxComponent::CheckBoxComponent (Magical8bitPlug2AudioProcessor& p, String paramId, String name)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    toggleButton.reset (new ToggleButton ("toggle button"));
    addAndMakeVisible (toggleButton.get());
    toggleButton->setButtonText (TRANS("new toggle button"));
    toggleButton->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (360, 28);


    //[Constructor] You can add your own custom stuff here..
    attc.reset (new ButtonAttachment (p.parameters, paramId, *toggleButton));

    toggleButton->setButtonText (name);
    //[/Constructor]
}

CheckBoxComponent::~CheckBoxComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    attc.reset();
    //[/Destructor_pre]

    toggleButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CheckBoxComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void CheckBoxComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    toggleButton->setBounds (32, 0, getWidth() - 40, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void CheckBoxComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == toggleButton.get())
    {
        //[UserButtonCode_toggleButton] -- add your button handler code here..
        //[/UserButtonCode_toggleButton]
    }

    //[UserbuttonClicked_Post]
    if (buttonThatWasClicked == toggleButton.get() && checkBoxListener != nullptr)
    {
        checkBoxListener->buttonClicked (buttonThatWasClicked);
    }

    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void CheckBoxComponent::setListener (Button::Listener* lnr)
{
    checkBoxListener = lnr;
}

void CheckBoxComponent::removeListener()
{
    checkBoxListener = nullptr;
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="CheckBoxComponent" componentName=""
                 parentClasses="public Component" constructorParams="Magical8bitPlug2AudioProcessor&amp; p, String paramId, String name"
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="1" initialWidth="360" initialHeight="28">
  <BACKGROUND backgroundColour="ffffff"/>
  <TOGGLEBUTTON name="toggle button" id="78b65dc9a6b61921" memberName="toggleButton"
                virtualName="" explicitFocusOrder="0" pos="32 0 40M 24" buttonText="new toggle button"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

