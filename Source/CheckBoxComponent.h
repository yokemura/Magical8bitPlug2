/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.5

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "Defs.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class CheckBoxComponent  : public Component,
    public Button::Listener
{
public:
    //==============================================================================
    CheckBoxComponent (Magical8bitPlug2AudioProcessor& p, String paramId, String name);
    ~CheckBoxComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void setListener (Button::Listener* lnr);
    void removeListener();
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    std::unique_ptr<ButtonAttachment> attc;
    Button::Listener* checkBoxListener = nullptr;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<ToggleButton> toggleButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CheckBoxComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

