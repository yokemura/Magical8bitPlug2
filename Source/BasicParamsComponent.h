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
#include "PluginProcessor.h"
#include "SliderComponent.h"
#include "ChoiceComponent.h"
#include "CheckBoxComponent.h"
class Magical8bitPlug2AudioProcessorEditor;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class BasicParamsComponent  : public Component,
                              public ComboBox::Listener,
                              public juce::Slider::Listener,
                              public juce::Button::Listener
{
public:
    //==============================================================================
    BasicParamsComponent (Magical8bitPlug2AudioProcessor& p, Magical8bitPlug2AudioProcessorEditor& e);
    ~BasicParamsComponent() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void sliderValueChanged (juce::Slider* sliderThatWasMoved) override;
    void buttonClicked (juce::Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    Magical8bitPlug2AudioProcessor& processor;
    Magical8bitPlug2AudioProcessorEditor& editor;

    std::unique_ptr<SliderAttachment> attc;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::Label> polyLabel;
    std::unique_ptr<SliderComponent> gainSlider;
    std::unique_ptr<ChoiceComponent> oscChoice;
    std::unique_ptr<juce::Slider> polyNumberInput;
    std::unique_ptr<CheckBoxComponent> advancedSwitch;
    std::unique_ptr<ChoiceComponent> colorSchemeChoice;
    std::unique_ptr<juce::TextButton> monoButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BasicParamsComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

