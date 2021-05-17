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

#include "MonophonicComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MonophonicComponent::MonophonicComponent (Magical8bitPlug2AudioProcessor& p)
    : processor(p)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    label.reset (new juce::Label ("label",
                                  TRANS("Monophonic Options")));
    addAndMakeVisible (label.get());
    label->setFont (juce::Font (17.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    label->setJustificationType (juce::Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label->setBounds (0, 4, 150, 22);

    behaviorChoice.reset (new ChoiceComponent (p, "monophonicBehavior_raw", "Behavior"));
    addAndMakeVisible (behaviorChoice.get());
    behaviorChoice->setName ("behavior selector");

    behaviorChoice->setBounds (0, 28, 224, 26);

    intervalChoice.reset (new ChoiceComponent (p, "arpeggioIntervalType_raw", "Interval"));
    addAndMakeVisible (intervalChoice.get());
    intervalChoice->setName ("interval selector");

    intervalChoice->setBounds (228, 28, 185, 28);

    intervalSlider.reset (new juce::Slider ("interval slider"));
    addAndMakeVisible (intervalSlider.get());
    intervalSlider->setRange (0, 10, 0.01);
    intervalSlider->setSliderStyle (juce::Slider::LinearHorizontal);
    intervalSlider->setTextBoxStyle (juce::Slider::TextBoxRight, false, 50, 20);

    portamentoSlider.reset (new SliderComponent (p, "portamentoTime", "Portamento"));
    addAndMakeVisible (portamentoSlider.get());
    portamentoSlider->setName ("portamento slider");


    //[UserPreSize]
    //[/UserPreSize]

    setSize (640, 82);


    //[Constructor] You can add your own custom stuff here..
    attc.reset (new SliderAttachment (p.parameters, "arpeggioIntervalSliderValue", *intervalSlider));
    behaviorChoice->setListener(this);
    intervalChoice->setListener(this);
    updateVisibility();
    //[/Constructor]
}

MonophonicComponent::~MonophonicComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    attc.reset();
    //[/Destructor_pre]

    label = nullptr;
    behaviorChoice = nullptr;
    intervalChoice = nullptr;
    intervalSlider = nullptr;
    portamentoSlider = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MonophonicComponent::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MonophonicComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    intervalSlider->setBounds (getWidth() - (getWidth() - 420), 28, getWidth() - 420, 24);
    portamentoSlider->setBounds (getWidth() - proportionOfWidth (0.5000f), 28, proportionOfWidth (0.5000f), 28);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void MonophonicComponent::comboBoxChanged(juce::ComboBox *comboBoxThatHasChanged) {
    updateVisibility();
}

void MonophonicComponent::updateVisibility()
{
    portamentoSlider->setVisible(false);
    intervalSlider->setVisible(false);
    intervalChoice->setVisible(false);

    switch (processor.settingRefs.monophonicBehavior()) {
        case kLegato:
            portamentoSlider->setVisible(true);
            break;
        case kArpeggioUp:
        case kArpeggioDown:
            intervalChoice->setVisible(true);
            switch (processor.settingRefs.apreggioIntervalType()) {
                case kSlider:
                    intervalSlider->setVisible(true);
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MonophonicComponent" componentName=""
                 parentClasses="public Component, public ComboBox::Listener" constructorParams="Magical8bitPlug2AudioProcessor&amp; p"
                 variableInitialisers="processor(p)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="640"
                 initialHeight="82">
  <BACKGROUND backgroundColour="ffffff"/>
  <LABEL name="label" id="bae3132bcad681ce" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="0 4 150 22" edTextCol="ff000000"
         edBkgCol="0" labelText="Monophonic Options" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="17.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <GENERICCOMPONENT name="behavior selector" id="fa2387d441a3005d" memberName="behaviorChoice"
                    virtualName="" explicitFocusOrder="0" pos="0 28 224 26" class="ChoiceComponent"
                    params="p, &quot;monophonicBehavior_raw&quot;, &quot;Behavior&quot;"/>
  <GENERICCOMPONENT name="interval selector" id="21d73ddc37680dd7" memberName="intervalChoice"
                    virtualName="" explicitFocusOrder="0" pos="228 28 185 28" class="ChoiceComponent"
                    params="p, &quot;arpeggioIntervalType_raw&quot;, &quot;Interval&quot;"/>
  <SLIDER name="interval slider" id="2d6901c46e73c1e" memberName="intervalSlider"
          virtualName="" explicitFocusOrder="0" pos="0Rr 28 420M 24" min="0.0"
          max="10.0" int="0.01" style="LinearHorizontal" textBoxPos="TextBoxRight"
          textBoxEditable="1" textBoxWidth="50" textBoxHeight="20" skewFactor="1.0"
          needsCallback="0"/>
  <GENERICCOMPONENT name="portamento slider" id="b01ddc412ec6dc27" memberName="portamentoSlider"
                    virtualName="" explicitFocusOrder="0" pos="0Rr 28 50% 28" class="SliderComponent"
                    params="p, &quot;portamentoTime&quot;, &quot;Portamento&quot;"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

