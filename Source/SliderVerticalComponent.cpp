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

#include "SliderVerticalComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
SliderVerticalComponent::SliderVerticalComponent (Magical8bitPlug2AudioProcessor& p, String paramId)
    : processor(p)
{
    //[Constructor_pre] You can add your own custom stuff here..
    setInterceptsMouseClicks(true, false);
    for (int i = 0; i < 64; i++)
    {
        verticalSliders[i].reset(new juce::Slider("vertical slider"));
        addAndMakeVisible(verticalSliders[i].get());
        verticalSliders[i]->setRange(0, 63, 0);
        verticalSliders[i]->setSliderStyle(juce::Slider::LinearBarVertical);
        verticalSliders[i]->setTextBoxStyle(juce::Slider::NoTextBox, true, 30, 20);
        verticalSliders[i]->setBounds(0 + i * 8, 0, 9, 250);
        verticalSliders[i]->setInterceptsMouseClicks(false, false);
        attc[i].reset(new SliderAttachment(p.parameters, paramId + String(i), *verticalSliders[i]));
    }
    //[/Constructor_pre]


    //[UserPreSize]
    //[/UserPreSize]

    setSize (513, 250);


    //[Constructor] You can add your own custom stuff here..
    baseMaxValue = 63;
    //[/Constructor]
}

SliderVerticalComponent::~SliderVerticalComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    for (int i = 0; i < 64; i++)
    {
        attc[i].reset();
        verticalSliders[i] = nullptr;
    }
    //[/Destructor_pre]



    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void SliderVerticalComponent::paint (juce::Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void SliderVerticalComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void SliderVerticalComponent::mouseDown (const juce::MouseEvent& e)
{
    //[UserCode_mouseDown] -- Add your code here...
    mouseDrag(e);
    //[/UserCode_mouseDown]
}

void SliderVerticalComponent::mouseDrag (const juce::MouseEvent& e)
{
    //[UserCode_mouseDrag] -- Add your code here...
    int rate = (baseMaxValue + 1) / (maxValue + 1);
    int sliderIndex = jlimit(0, numWidth - 1, (int)floor(e.position.x / (getWidth() / ((double)numWidth))));
    waveValue = jlimit(0, baseMaxValue, (int)(baseMaxValue * ((double)getHeight() - (double)e.position.y) / ((double)getHeight()) + 0.5));
    waveValue = (int)(waveValue / rate);
    verticalSliders[sliderIndex]->setValue(((double)waveValue / maxValue * baseMaxValue));
    getParentComponent()->mouseDrag(e.getEventRelativeTo(getParentComponent()));
    //[/UserCode_mouseDrag]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void SliderVerticalComponent::setForm(int numWidth, int maxValue, int width, int height)
{
    this->numWidth = jlimit(0, 64, numWidth);
    this->maxValue = maxValue;

    int sliderWidth = width / this->numWidth;

    setSize(sliderWidth * this->numWidth + 1, height);
    
    int rate = (baseMaxValue + 1) / (maxValue + 1);

    for (int i = 0; i < 64; i++)
    {
        verticalSliders[i]->setBounds(0 + i * sliderWidth, 0, sliderWidth + 1, height);
        int value = verticalSliders[i]->getValue();
        verticalSliders[i]->setValue(((double)(value / rate) / maxValue * baseMaxValue));
        verticalSliders[i]->repaint();
    }
}

void SliderVerticalComponent::setValue(int index, int value)
{
    verticalSliders[index]->setValue(((double)value / maxValue * baseMaxValue));
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SliderVerticalComponent"
                 componentName="" parentClasses="public juce::Component" constructorParams="Magical8bitPlug2AudioProcessor&amp; p, String paramId"
                 variableInitialisers="processor(p)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="1" initialWidth="513"
                 initialHeight="250">
  <METHODS>
    <METHOD name="mouseDrag (const juce::MouseEvent&amp; e)"/>
    <METHOD name="mouseDown (const juce::MouseEvent&amp; e)"/>
  </METHODS>
  <BACKGROUND backgroundColour="ffffff"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

