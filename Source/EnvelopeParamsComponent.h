/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 6.1.5

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "SliderComponent.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class EnvelopeParamsComponent  : public Component
{
public:
    //==============================================================================
    EnvelopeParamsComponent (Magical8bitPlug2AudioProcessor& p);
    ~EnvelopeParamsComponent() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void enablementChanged() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    LookAndFeel_V4 warningLabelLookAndFeel;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::Label> label;
    std::unique_ptr<SliderComponent> attackSlider;
    std::unique_ptr<SliderComponent> decaySlider;
    std::unique_ptr<SliderComponent> sustainSlider;
    std::unique_ptr<SliderComponent> releaseSlider;
    std::unique_ptr<juce::Label> warningLabel;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EnvelopeParamsComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

