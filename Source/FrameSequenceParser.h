/*
  ==============================================================================

    FrameSequenceParser.h
    Created: 11 Dec 2019 8:49:02am
    Author:  除村 武志

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "FrameSequence.h"
#include "FrameSequenceParseErrors.h"

struct FrameSequenceParser
{
    FrameSequence parse (const String& input, int minValue, int maxValue, ParseError* error);
};
