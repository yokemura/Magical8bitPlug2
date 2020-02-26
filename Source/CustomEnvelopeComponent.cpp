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
#include "FrameSequenceParseErrors.h"
//[/Headers]

#include "CustomEnvelopeComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
CustomEnvelopeComponent::CustomEnvelopeComponent (Magical8bitPlug2AudioProcessor& p, String type, String displayName, String flagParameterName)
    : processor(p)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    textEditor.reset (new TextEditor ("text editor"));
    addAndMakeVisible (textEditor.get());
    textEditor->setMultiLine (false);
    textEditor->setReturnKeyStartsNewLine (false);
    textEditor->setReadOnly (false);
    textEditor->setScrollbarsShown (false);
    textEditor->setCaretVisible (true);
    textEditor->setPopupMenuEnabled (true);
    textEditor->setText (String());

    toggleButton.reset (new ToggleButton ("toggle button"));
    addAndMakeVisible (toggleButton.get());
    toggleButton->setButtonText (TRANS("Enabled"));
    toggleButton->addListener (this);

    toggleButton->setBounds (8, 4, 104, 24);

    label.reset (new Label ("new label",
                            String()));
    addAndMakeVisible (label.get());
    label->setFont (Font (12.00f, Font::plain).withTypefaceStyle ("Regular"));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (540, 56);


    //[Constructor] You can add your own custom stuff here..
    paramType = type;
    attc.reset (new ButtonAttachment (p.parameters, flagParameterName, *toggleButton));

    textEditor->addListener (this);
    textEditor->setText (p.settingRefs.getSequenceString (type));

    toggleButton->setButtonText (displayName);
    //[/Constructor]
}

CustomEnvelopeComponent::~CustomEnvelopeComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    textEditor = nullptr;
    toggleButton = nullptr;
    label = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    attc.reset();
    //[/Destructor]
}

//==============================================================================
void CustomEnvelopeComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void CustomEnvelopeComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    textEditor->setBounds (112, 4, getWidth() - 124, 24);
    label->setBounds (112, 28, getWidth() - 124, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void CustomEnvelopeComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == toggleButton.get())
    {
        //[UserButtonCode_toggleButton] -- add your button handler code here..
        //[/UserButtonCode_toggleButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void CustomEnvelopeComponent::lookAndFeelChanged()
{
    //[UserCode_lookAndFeelChanged] -- Add your code here...
    ColorScheme cs = ColorScheme (processor.settingRefs.colorSchemeType());

    labelLookAndFeel.setColour (Label::textColourId, cs.warning);
    label->setLookAndFeel (&labelLookAndFeel);

    textEditor->applyColourToAllText (cs.mainThinLine, true);

    //[/UserCode_lookAndFeelChanged]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void CustomEnvelopeComponent::textEditorTextChanged (TextEditor& editor)
{
    printf ("*** text changed!\n");
    String txt = editor.getText();

    ParseError err = kParseErrorNone;
    processor.settingRefs.setSequenceWithString (paramType, txt, &err);

    if (err == kParseErrorValueOutOfRange)
    {
        if (paramType == "volume")
        {
            label->setText (getParseErrorString (err, 0, 15), dontSendNotification);
        }
        else if (paramType == "pitch")
        {
            label->setText (getParseErrorString (err, -64, 63), dontSendNotification);
        }
        else if (paramType == "duty")
        {
            label->setText (getParseErrorString (err, 0, 2), dontSendNotification);
        }
    }
    else
    {
        label->setText (getParseErrorString (err), dontSendNotification);
    }
}

void CustomEnvelopeComponent::sequenceChanged (String& str)
{
    textEditor->setText (str);
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="CustomEnvelopeComponent"
                 componentName="" parentClasses="public Component, TextEditor::Listener, FrameSequenceChangeListener"
                 constructorParams="Magical8bitPlug2AudioProcessor&amp; p, String type, String displayName, String flagParameterName"
                 variableInitialisers="processor(p)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="540"
                 initialHeight="56">
  <METHODS>
    <METHOD name="lookAndFeelChanged()"/>
  </METHODS>
  <BACKGROUND backgroundColour="ffffff"/>
  <TEXTEDITOR name="text editor" id="9e63a9c08f238222" memberName="textEditor"
              virtualName="" explicitFocusOrder="0" pos="112 4 124M 24" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="0" scrollbars="0"
              caret="1" popupmenu="1"/>
  <TOGGLEBUTTON name="toggle button" id="87baaa12bb810ff" memberName="toggleButton"
                virtualName="" explicitFocusOrder="0" pos="8 4 104 24" buttonText="Enabled"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <LABEL name="new label" id="ea955df87cc606d6" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="112 28 124M 24" edTextCol="ff000000"
         edBkgCol="0" labelText="" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="12.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

