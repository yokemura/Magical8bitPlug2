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

#include "WaveformParamsComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
WaveformParamsComponent::WaveformParamsComponent (Magical8bitPlug2AudioProcessor& p)
    : processor(p)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    sliderVerticalComponent.reset (new SliderVerticalComponent (p, "waveformWave"));
    addAndMakeVisible (sliderVerticalComponent.get());
    sliderVerticalComponent->setName ("slider vertical component");

    sliderVerticalComponent->setBounds (10, 34, 513, 250);

    label.reset (new juce::Label ("label",
                                  TRANS("Waveform")));
    addAndMakeVisible (label.get());
    label->setFont (juce::Font (17.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    label->setJustificationType (juce::Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    label->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    label->setBounds (0, 4, 150, 22);

    waveformWaveText.reset (new juce::TextEditor ("waveform wave text"));
    addAndMakeVisible (waveformWaveText.get());
    waveformWaveText->setMultiLine (false);
    waveformWaveText->setReturnKeyStartsNewLine (false);
    waveformWaveText->setReadOnly (true);
    waveformWaveText->setScrollbarsShown (false);
    waveformWaveText->setCaretVisible (false);
    waveformWaveText->setPopupMenuEnabled (false);
    waveformWaveText->setText (juce::String());

    waveformWaveText->setBounds (472, 8, 50, 20);

    waveformComboX.reset (new juce::ComboBox ("waveform combo x"));
    addAndMakeVisible (waveformComboX.get());
    waveformComboX->setEditableText (false);
    waveformComboX->setJustificationType (juce::Justification::centredLeft);
    waveformComboX->setTextWhenNothingSelected (juce::String());
    waveformComboX->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    waveformComboX->addListener (this);

    waveformComboX->setBounds (40, 296, 80, 24);

    waveformXLabel.reset (new juce::Label ("waveform x label",
                                           TRANS("X")));
    addAndMakeVisible (waveformXLabel.get());
    waveformXLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    waveformXLabel->setJustificationType (juce::Justification::centredLeft);
    waveformXLabel->setEditable (false, false, false);
    waveformXLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    waveformXLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    waveformXLabel->setBounds (16, 296, 24, 24);

    waveformYLabel.reset (new juce::Label ("waveform y label",
                                           TRANS("Y")));
    addAndMakeVisible (waveformYLabel.get());
    waveformYLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    waveformYLabel->setJustificationType (juce::Justification::centredLeft);
    waveformYLabel->setEditable (false, false, false);
    waveformYLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    waveformYLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    waveformYLabel->setBounds (136, 296, 24, 24);

    waveformComboY.reset (new juce::ComboBox ("waveform combo y"));
    addAndMakeVisible (waveformComboY.get());
    waveformComboY->setEditableText (false);
    waveformComboY->setJustificationType (juce::Justification::centredLeft);
    waveformComboY->setTextWhenNothingSelected (juce::String());
    waveformComboY->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    waveformComboY->addListener (this);

    waveformComboY->setBounds (160, 296, 80, 24);

    waveformTemplateLabel.reset (new juce::Label ("waveform template label",
                                                  TRANS("Template")));
    addAndMakeVisible (waveformTemplateLabel.get());
    waveformTemplateLabel->setFont (juce::Font (15.00f, juce::Font::plain).withTypefaceStyle ("Regular"));
    waveformTemplateLabel->setJustificationType (juce::Justification::centredLeft);
    waveformTemplateLabel->setEditable (false, false, false);
    waveformTemplateLabel->setColour (juce::TextEditor::textColourId, juce::Colours::black);
    waveformTemplateLabel->setColour (juce::TextEditor::backgroundColourId, juce::Colour (0x00000000));

    waveformTemplateLabel->setBounds (280, 296, 72, 24);

    waveformComboTemplate.reset (new juce::ComboBox ("waveform combo template"));
    addAndMakeVisible (waveformComboTemplate.get());
    waveformComboTemplate->setEditableText (false);
    waveformComboTemplate->setJustificationType (juce::Justification::centredLeft);
    waveformComboTemplate->setTextWhenNothingSelected (juce::String());
    waveformComboTemplate->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    waveformComboTemplate->addListener (this);

    waveformComboTemplate->setBounds (352, 296, 168, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (536, 340);


    //[Constructor] You can add your own custom stuff here..
    AudioParameterChoice* cX = (AudioParameterChoice*)p.parameters.getParameter("waveformX");
    for (int i = 0; i < cX->choices.size(); i++)
    {
        String choice = cX->choices[i];
        waveformComboX->addItem(choice, i + 1);
    }
    waveformComboX->setSelectedItemIndex(cX->getIndex());
    attcX.reset(new ComboBoxAttachment(p.parameters, "waveformX", *waveformComboX));

    AudioParameterChoice* cY = (AudioParameterChoice*)p.parameters.getParameter("waveformY");
    for (int i = 0; i < cY->choices.size(); i++)
    {
        String choice = cY->choices[i];
        waveformComboY->addItem(choice, i + 1);
    }
    waveformComboY->setSelectedItemIndex(cY->getIndex());
    attcY.reset(new ComboBoxAttachment(p.parameters, "waveformY", *waveformComboY));

    AudioParameterChoice* cTemplate = (AudioParameterChoice*)p.parameters.getParameter("waveformTemplate");
    for (int i = 0; i < cTemplate->choices.size(); i++)
    {
        String choice = cTemplate->choices[i];
        waveformComboTemplate->addItem(choice, i + 1);
    }
    waveformComboTemplate->setSelectedItemIndex(cTemplate->getIndex());
    attcTemplate.reset(new ComboBoxAttachment(p.parameters, "waveformTemplate", *waveformComboTemplate));

    int fontHeight = waveformWaveText->getFont().getHeight();
    int topIndent = (waveformWaveText->getHeight() - fontHeight) / 2;
    int fontWidth = fontHeight;
    int leftIndent = (waveformWaveText->getWidth() - fontWidth) / 2;
    waveformWaveText->setBorder(BorderSize<int>(0, 0, 0, 0));
    waveformWaveText->setIndents(leftIndent, topIndent);
    //[/Constructor]
}

WaveformParamsComponent::~WaveformParamsComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    attcX.reset();
    attcY.reset();
    attcTemplate.reset();
    //[/Destructor_pre]

    sliderVerticalComponent = nullptr;
    label = nullptr;
    waveformWaveText = nullptr;
    waveformComboX = nullptr;
    waveformXLabel = nullptr;
    waveformYLabel = nullptr;
    waveformComboY = nullptr;
    waveformTemplateLabel = nullptr;
    waveformComboTemplate = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void WaveformParamsComponent::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void WaveformParamsComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void WaveformParamsComponent::comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == waveformComboX.get())
    {
        //[UserComboBoxCode_waveformComboX] -- add your combo box handling code here..
        sliderVerticalComponent->setForm(processor.settingRefs.getWaveformX(), processor.settingRefs.getWaveformY(), 513, 250);
        //[/UserComboBoxCode_waveformComboX]
    }
    else if (comboBoxThatHasChanged == waveformComboY.get())
    {
        //[UserComboBoxCode_waveformComboY] -- add your combo box handling code here..
        sliderVerticalComponent->setForm(processor.settingRefs.getWaveformX(), processor.settingRefs.getWaveformY(), 513, 250);
        //[/UserComboBoxCode_waveformComboY]
    }
    else if (comboBoxThatHasChanged == waveformComboTemplate.get())
    {
        //[UserComboBoxCode_waveformComboTemplate] -- add your combo box handling code here..
        //0:"Custom", 1:"Sine", 2:"Triangle", 3:"Sawtooth", 4:"Square 6.25%", 5:"Square 18.75%", 6:"Square 31.25%", 7:"Square 37.5%", 8:"Square 43.75%"
        int x = processor.settingRefs.getWaveformX();
        int y = processor.settingRefs.getWaveformY();
        if (waveformComboTemplate->getSelectedItemIndex() == 1)
        {
            double twopi = MathConstants<float>::pi * 2.0;
            for (int i = 0; i < x; i++)
            {
                sliderVerticalComponent->setValue(i, (int)((std::sin(twopi * i / x) + 1.0) * y / 2.0 + 0.5));
            }
        }
        else if (waveformComboTemplate->getSelectedItemIndex() == 2)
        {
            for (int i = 0; i < (x / 2); i++)
            {
                sliderVerticalComponent->setValue(i, (int)(i * (double)y / (x / 2 - 1) + 0.5));
                sliderVerticalComponent->setValue(i + (x / 2), (int)(y - i * (double)y / (x / 2 - 1) + 0.5));
            }
        }
        else if (waveformComboTemplate->getSelectedItemIndex() == 3)
        {
            for (int i = 0; i < x; i++)
            {
                sliderVerticalComponent->setValue(i, (int)(i * (double)y / (x - 1) + 0.5));
            }
        }
        else if (waveformComboTemplate->getSelectedItemIndex() >= 4 && waveformComboTemplate->getSelectedItemIndex() <= 8)
        {
            double duty[5] = { 0.0625, 0.1875, 0.3125, 0.375, 0.4375 };
            for (int i = 0; i < (int)(x * duty[waveformComboTemplate->getSelectedItemIndex() - 4]); i++)
            {
                sliderVerticalComponent->setValue(i, 0);
            }
            for (int i = (int)(x * duty[waveformComboTemplate->getSelectedItemIndex() - 4]); i < x; i++)
            {
                sliderVerticalComponent->setValue(i, y);
            }
        }
        waveformComboTemplate->setSelectedItemIndex(0);
        //[/UserComboBoxCode_waveformComboTemplate]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}

void WaveformParamsComponent::mouseDrag (const juce::MouseEvent& e)
{
    //[UserCode_mouseDrag] -- Add your code here...
    int waveValue = sliderVerticalComponent->waveValue;
    if (waveValue >= 0)
    {
        waveformWaveText->setText(String(waveValue));
    }
    //[/UserCode_mouseDrag]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void WaveformParamsComponent::sliderRepaint()
{
    sliderVerticalComponent->setForm(processor.settingRefs.getWaveformX(), processor.settingRefs.getWaveformY(), 513, 250);
}

//void WaveformParamsComponent::sliderInit()
//{
//    for (int i = 0; i < 64; i++)
//    {
//        //sliderVerticalComponent->verticalSliders[i]->setValue(0);
//        sliderVerticalComponent->verticalSliders[i]->setRange(0, 63, 1);
//        //sliderVerticalComponent->verticalSliders[i]->repaint();
//    }
//}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="WaveformParamsComponent"
                 componentName="" parentClasses="public Component" constructorParams="Magical8bitPlug2AudioProcessor&amp; p"
                 variableInitialisers="processor(p)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="536"
                 initialHeight="340">
  <METHODS>
    <METHOD name="mouseDrag (const juce::MouseEvent&amp; e)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ffffff"/>
  <GENERICCOMPONENT name="slider vertical component" id="d3c5ea1dec0891ea" memberName="sliderVerticalComponent"
                    virtualName="" explicitFocusOrder="0" pos="10 34 513 250" class="SliderVerticalComponent"
                    params="p, &quot;waveformWave&quot;"/>
  <LABEL name="label" id="bae3132bcad681ce" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="0 4 150 22" edTextCol="ff000000"
         edBkgCol="0" labelText="Waveform" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="17.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTEDITOR name="waveform wave text" id="a0d4c4fff23ba9a7" memberName="waveformWaveText"
              virtualName="" explicitFocusOrder="0" pos="472 8 50 20" initialText=""
              multiline="0" retKeyStartsLine="0" readonly="1" scrollbars="0"
              caret="0" popupmenu="0"/>
  <COMBOBOX name="waveform combo x" id="47a8fb84e28a923b" memberName="waveformComboX"
            virtualName="" explicitFocusOrder="0" pos="40 296 80 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="waveform x label" id="80e4ef8bbf096c16" memberName="waveformXLabel"
         virtualName="" explicitFocusOrder="0" pos="16 296 24 24" edTextCol="ff000000"
         edBkgCol="0" labelText="X" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="waveform y label" id="9d743f56f93330a9" memberName="waveformYLabel"
         virtualName="" explicitFocusOrder="0" pos="136 296 24 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Y" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="waveform combo y" id="519e5c60d0487582" memberName="waveformComboY"
            virtualName="" explicitFocusOrder="0" pos="160 296 80 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="waveform template label" id="c0bf04a500a0f7b" memberName="waveformTemplateLabel"
         virtualName="" explicitFocusOrder="0" pos="280 296 72 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Template" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="waveform combo template" id="a71bba02a0c84649" memberName="waveformComboTemplate"
            virtualName="" explicitFocusOrder="0" pos="352 296 168 24" editable="0"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

