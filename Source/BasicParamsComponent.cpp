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
#include "PluginEditor.h"
//[/Headers]

#include "BasicParamsComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
BasicParamsComponent::BasicParamsComponent (Magical8bitPlug2AudioProcessor& p, Magical8bitPlug2AudioProcessorEditor& e)
    : processor(p),editor(e)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    polyLabel.reset (new Label ("label",
                                TRANS("Poly")));
    addAndMakeVisible (polyLabel.get());
    polyLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    polyLabel->setJustificationType (Justification::centredLeft);
    polyLabel->setEditable (false, false, false);
    polyLabel->setColour (TextEditor::textColourId, Colours::black);
    polyLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    polyLabel->setBounds (232, 8, 40, 15);

    gainSlider.reset (new SliderComponent (p, "gain", "Gain"));
    addAndMakeVisible (gainSlider.get());
    gainSlider->setName ("gain slider");

    gainSlider->setBounds (0, 32, 360, 32);

    oscChoice.reset (new ChoiceComponent (p, "osc", "OSC Type"));
    addAndMakeVisible (oscChoice.get());
    oscChoice->setName ("osc selector");

    oscChoice->setBounds (0, 4, 224, 28);

    polyNumberInput.reset (new Slider ("poly number input"));
    addAndMakeVisible (polyNumberInput.get());
    polyNumberInput->setRange (0, 32, 1);
    polyNumberInput->setSliderStyle (Slider::IncDecButtons);
    polyNumberInput->setTextBoxStyle (Slider::TextBoxLeft, false, 30, 20);
    polyNumberInput->addListener (this);

    polyNumberInput->setBounds (268, 4, 86, 24);

    advancedSwitch.reset (new CheckBoxComponent (p, "isAdvancedPanelOpen_raw", "Show Advanced Options"));
    addAndMakeVisible (advancedSwitch.get());
    advancedSwitch->setName ("advanced option switch");

    colorSchemeChoice.reset (new ChoiceComponent (p, "colorScheme", "Color"));
    addAndMakeVisible (colorSchemeChoice.get());
    colorSchemeChoice->setName ("color selector");


    //[UserPreSize]
    //[/UserPreSize]

    setSize (700, 64);


    //[Constructor] You can add your own custom stuff here..
    oscChoice->setListener (this);
    advancedSwitch->setListener (this);
    colorSchemeChoice->setListener (this);
    colorSchemeChoice->setVisible (p.settingRefs.isAdvancedPanelOpen());
    attc.reset (new SliderAttachment (p.parameters, "maxPoly", *polyNumberInput));
    //[/Constructor]
}

BasicParamsComponent::~BasicParamsComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    oscChoice->removeListener();
    advancedSwitch->removeListener();
    attc.reset();
    //[/Destructor_pre]

    polyLabel = nullptr;
    gainSlider = nullptr;
    oscChoice = nullptr;
    polyNumberInput = nullptr;
    advancedSwitch = nullptr;
    colorSchemeChoice = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void BasicParamsComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void BasicParamsComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    advancedSwitch->setBounds (getWidth() - 240, 4, 240, 28);
    colorSchemeChoice->setBounds (getWidth() - 4 - 185, 32, 185, 28);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void BasicParamsComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == polyNumberInput.get())
    {
        //[UserSliderCode_polyNumberInput] -- add your slider handling code here..
        processor.setupVoice();
        //[/UserSliderCode_polyNumberInput]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void BasicParamsComponent::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    processor.setupVoice();
    editor.resized();
    printf ("setup voice!!\n");
}

void BasicParamsComponent::buttonClicked (Button* buttonThatWasClicked)
{
    colorSchemeChoice->setVisible (buttonThatWasClicked->getToggleState());
    editor.resizeWholePanel();
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="BasicParamsComponent" componentName=""
                 parentClasses="public Component, public ComboBox::Listener, public Button::Listener"
                 constructorParams="Magical8bitPlug2AudioProcessor&amp; p, Magical8bitPlug2AudioProcessorEditor&amp; e"
                 variableInitialisers="processor(p),editor(e)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.330" fixedSize="1"
                 initialWidth="700" initialHeight="64">
  <BACKGROUND backgroundColour="ffffff"/>
  <LABEL name="label" id="a5b2b89e6dca4fe" memberName="polyLabel" virtualName=""
         explicitFocusOrder="0" pos="232 8 40 15" edTextCol="ff000000"
         edBkgCol="0" labelText="Poly" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <GENERICCOMPONENT name="gain slider" id="4bb22b329fed19e9" memberName="gainSlider"
                    virtualName="" explicitFocusOrder="0" pos="0 32 360 32" class="SliderComponent"
                    params="p, &quot;gain&quot;, &quot;Gain&quot;"/>
  <GENERICCOMPONENT name="osc selector" id="fa2387d441a3005d" memberName="oscChoice"
                    virtualName="" explicitFocusOrder="0" pos="0 4 224 28" class="ChoiceComponent"
                    params="p, &quot;osc&quot;, &quot;OSC Type&quot;"/>
  <SLIDER name="poly number input" id="f767aca03a9fe3ae" memberName="polyNumberInput"
          virtualName="" explicitFocusOrder="0" pos="268 4 86 24" min="0.0"
          max="32.0" int="1.0" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="30" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <GENERICCOMPONENT name="advanced option switch" id="9d35239102eeb521" memberName="advancedSwitch"
                    virtualName="" explicitFocusOrder="0" pos="0Rr 4 240 28" class="CheckBoxComponent"
                    params="p, &quot;isAdvancedPanelOpen_raw&quot;, &quot;Show Advanced Options&quot;"/>
  <GENERICCOMPONENT name="color selector" id="21d73ddc37680dd7" memberName="colorSchemeChoice"
                    virtualName="" explicitFocusOrder="0" pos="4Rr 32 185 28" class="ChoiceComponent"
                    params="p, &quot;colorScheme&quot;, &quot;Color&quot;"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

