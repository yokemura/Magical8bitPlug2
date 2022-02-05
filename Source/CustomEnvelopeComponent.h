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
class CustomEnvelopeComponent  : public Component,
                                 TextEditor::Listener,
                                 FrameSequenceChangeListener,
                                 public juce::Button::Listener
{
public:
    //==============================================================================
    CustomEnvelopeComponent (Magical8bitPlug2AudioProcessor& p, String type, String displayName, String flagParameterName);
    ~CustomEnvelopeComponent() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void textEditorTextChanged (TextEditor& editor) override;
    void sequenceChanged (String& str) override;
    //[/UserMethods]

    void paint (juce::Graphics& g) override;
    void resized() override;
    void buttonClicked (juce::Button* buttonThatWasClicked) override;
    void lookAndFeelChanged() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    Magical8bitPlug2AudioProcessor& processor;
    std::unique_ptr<ButtonAttachment> attc;
    String paramType;
    LookAndFeel_V4 labelLookAndFeel;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<juce::TextEditor> textEditor;
    std::unique_ptr<juce::ToggleButton> toggleButton;
    std::unique_ptr<juce::Label> label;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomEnvelopeComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

