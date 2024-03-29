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

struct SegmentIndexes {
    static const int NONE = -1;
    
    int releaseBlockIndex = NONE;
    int repeatStartIndex = NONE;
    int repeatEndIndex = NONE;
    ParseError error;
};

struct FrameSequenceParser
{
    /*
     Public
     */
    FrameSequence parse (const String& input, int minValue, int maxValue, ParseError* error);
    
    /*
     Semantically private (leave them open for unit testing)
     */
    std::vector<int> parseSlope (const String& input,
                                 int minValue,
                                 int maxValue,
                                 ParseError* error);
    std::vector<int> parseHold (const String& input,
                                  int minValue,
                                  int maxValue,
                                  ParseError* error);
    std::vector<int> parseSegment (const String& input,
                                   int minValue,
                                   int maxValue,
                                   ParseError* error);
    void splitSegment (const String& input,
                       SegmentIndexes indexes,
                       String& beforeRepeat,
                       String& insideRepeat,
                       String& afterRelease);
    SegmentIndexes findSegment(const String& input);
};
