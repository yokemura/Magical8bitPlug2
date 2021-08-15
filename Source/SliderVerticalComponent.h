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

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Defs.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class SliderVerticalComponent  : public juce::Component
{
public:
    //==============================================================================
    SliderVerticalComponent (Magical8bitPlug2AudioProcessor& p, String paramId);
    ~SliderVerticalComponent() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void setForm(int numWidth, int maxValue, int width, int height);
    void setValue(int index, int value);
    int waveValue = -1;
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void mouseDown (const juce::MouseEvent& e) override;
    void mouseDrag (const juce::MouseEvent& e) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    std::unique_ptr<juce::Slider> verticalSliders[64];
    int numWidth;
    int maxValue;
    int baseMaxValue;
    Magical8bitPlug2AudioProcessor& processor;
    std::unique_ptr<SliderAttachment> attc[64];
    //[/UserVariables]

    //==============================================================================


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SliderVerticalComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

