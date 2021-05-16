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

#include "ChoiceComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ChoiceComponent::ChoiceComponent (Magical8bitPlug2AudioProcessor& p, String paramId, String name)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    comboBox.reset (new ComboBox ("combo box"));
    addAndMakeVisible (comboBox.get());
    comboBox->setEditableText (false);
    comboBox->setJustificationType (Justification::centredLeft);
    comboBox->setTextWhenNothingSelected (String());
    comboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    comboBox->addListener (this);

    label.reset (new Label ("label",
                            TRANS("Label")));
    addAndMakeVisible (label.get());
    label->setFont (Font (14.00f, Font::plain).withTypefaceStyle ("Regular"));
    label->setJustificationType (Justification::centredRight);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label->setBounds (8, 1, 60, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (360, 28);


    //[Constructor] You can add your own custom stuff here..
    label->setText (name, dontSendNotification);

    AudioParameterChoice* c = (AudioParameterChoice*)p.parameters.getParameter (paramId);

    for (int i = 0; i < c->choices.size(); i++)
    {
        String choice = c->choices[i];
        comboBox->addItem (choice, i + 1);
    }

    attc.reset (new ComboBoxAttachment (p.parameters, paramId, *comboBox));
    //[/Constructor]
}

ChoiceComponent::~ChoiceComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    attc.reset();
    //[/Destructor_pre]

    comboBox = nullptr;
    label = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ChoiceComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ChoiceComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    comboBox->setBounds (72, 0, getWidth() - 80, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ChoiceComponent::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == comboBox.get())
    {
        //[UserComboBoxCode_comboBox] -- add your combo box handling code here..
        //  printf ("value = %d\n", comboBoxThatHasChanged->getSelectedId());
        //[/UserComboBoxCode_comboBox]
    }

    //[UsercomboBoxChanged_Post]
    if (comboBoxThatHasChanged == comboBox.get() && comboBoxListener != nullptr)
    {
        comboBoxListener->comboBoxChanged (comboBoxThatHasChanged);
    }

    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void ChoiceComponent::setListener (ComboBox::Listener* lnr)
{
    comboBoxListener = lnr;
}

void ChoiceComponent::removeListener()
{
    comboBoxListener = nullptr;
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ChoiceComponent" componentName=""
                 parentClasses="public Component" constructorParams="Magical8bitPlug2AudioProcessor&amp; p, String paramId, String name"
                 variableInitialisers="" snapPixels="8" snapActive="1" snapShown="1"
                 overlayOpacity="0.330" fixedSize="1" initialWidth="360" initialHeight="28">
  <BACKGROUND backgroundColour="ffffff"/>
  <COMBOBOX name="combo box" id="67bfdf47357e233d" memberName="comboBox"
            virtualName="" explicitFocusOrder="0" pos="72 0 80M 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="label" id="af1fa4a96c3448e5" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="8 1 60 24" edTextCol="ff000000" edBkgCol="0"
         labelText="Label" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="14.0"
         kerning="0.0" bold="0" italic="0" justification="34"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

