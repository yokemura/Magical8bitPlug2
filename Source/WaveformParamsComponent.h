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
#include "SliderVerticalComponent.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class WaveformParamsComponent  : public Component,
                                 public juce::ComboBox::Listener
{
public:
    //==============================================================================
    WaveformParamsComponent (Magical8bitPlug2AudioProcessor& p);
    ~WaveformParamsComponent() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void sliderRepaint();
    //void sliderInit();
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void comboBoxChanged (juce::ComboBox* comboBoxThatHasChanged) override;
    void mouseDrag (const juce::MouseEvent& e) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    Magical8bitPlug2AudioProcessor& processor;
    std::unique_ptr<ComboBoxAttachment> attcX;
    std::unique_ptr<ComboBoxAttachment> attcY;
    std::unique_ptr<ComboBoxAttachment> attcTemplate;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<SliderVerticalComponent> sliderVerticalComponent;
    std::unique_ptr<juce::Label> label;
    std::unique_ptr<juce::TextEditor> waveformWaveText;
    std::unique_ptr<juce::ComboBox> waveformComboX;
    std::unique_ptr<juce::Label> waveformXLabel;
    std::unique_ptr<juce::Label> waveformYLabel;
    std::unique_ptr<juce::ComboBox> waveformComboY;
    std::unique_ptr<juce::Label> waveformTemplateLabel;
    std::unique_ptr<juce::ComboBox> waveformComboTemplate;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformParamsComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

