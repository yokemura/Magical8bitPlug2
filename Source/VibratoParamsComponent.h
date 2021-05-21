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
#include "../JuceLibraryCode/JuceHeader.h"
#include "SliderComponent.h"
#include "CheckBoxComponent.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class VibratoParamsComponent  : public Component
{
public:
    //==============================================================================
    VibratoParamsComponent (Magical8bitPlug2AudioProcessor& p);
    ~VibratoParamsComponent() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::Label> label;
    std::unique_ptr<SliderComponent> ratioSlider;
    std::unique_ptr<SliderComponent> depthSlider;
    std::unique_ptr<SliderComponent> delaySlider;
    std::unique_ptr<CheckBoxComponent> ignoreWheelSwitch;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VibratoParamsComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

