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
#include "CustomEnvelopeComponent.h"
#include "ChoiceComponent.h"
#include "SliderComponent.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class AdvancedParamsComponent  : public Component
{
public:
    //==============================================================================
    AdvancedParamsComponent (Magical8bitPlug2AudioProcessor& p);
    ~AdvancedParamsComponent() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    Magical8bitPlug2AudioProcessor& processor;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<CustomEnvelopeComponent> volumeCompo;
    std::unique_ptr<juce::Label> label5;
    std::unique_ptr<CustomEnvelopeComponent> pitchCompo;
    std::unique_ptr<CustomEnvelopeComponent> dutyCompo;
    std::unique_ptr<ChoiceComponent> coarseOrFineChoice;
    std::unique_ptr<SliderComponent> bendResolutionSlider;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdvancedParamsComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

