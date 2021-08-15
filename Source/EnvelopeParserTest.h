/*
  ==============================================================================

    EnvelopeParserTest.h
    Created: 13 Aug 2021 6:14:32pm
    Author:  除村武志

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "FrameSequence.h"
#include "FrameSequenceParser.h"
#include "FrameSequenceParseErrors.h"

class EnvelopeParserTest : public UnitTest {

public:
    EnvelopeParserTest() : UnitTest("Custom Envelope Parser Test") {}
    
    void runTest() override
    {
        FrameSequenceParser parser;
                
        beginTest ("No repeat");
        String input1 = "aaa"; // At this phase it doesn't matter if it contains numbers or not
        auto result1 = parser.findSegment(input1);
        expect(result1.repeatStartIndex == SegmentIndexes::NONE);
        expect(result1.repeatEndIndex == SegmentIndexes::NONE);
        expect(result1.releaseBlockIndex == SegmentIndexes::NONE);

        beginTest ("With repeat, no release");
        String input2 = "aa[bbb]";
        auto result2 = parser.findSegment(input2);
        expect(result2.repeatStartIndex == 3);
        expect(result2.repeatEndIndex == 6);
        expect(result2.releaseBlockIndex == SegmentIndexes::NONE);
        
        beginTest ("Repeat segment starts from the top");
        String input3 = "[aaa]";
        auto result3 = parser.findSegment(input3);
        expect(result3.repeatStartIndex == 1);
        expect(result3.repeatEndIndex == 4);
        expect(result3.releaseBlockIndex == SegmentIndexes::NONE);

        beginTest ("No repeat, with release");
        String input4 = "aaa|bbbb";
        auto result4 = parser.findSegment(input4);
        expect(result4.repeatStartIndex == SegmentIndexes::NONE);
        expect(result4.repeatEndIndex == 3); // It doesn't repeat, but it has to keep the last index of pre-release segment
        expect(result4.releaseBlockIndex == 4);
        
        beginTest ("Release segment without pre-release segment");
        String input5 = "|bbbb";
        auto result5 = parser.findSegment(input5);
        expect(result5.repeatStartIndex == SegmentIndexes::NONE);
        expect(result5.repeatEndIndex == 0); // This results in an immediate transition to Release Phase
        expect(result5.releaseBlockIndex == 1);

        beginTest ("Repeat and release (no pre-repeat)");
        String input6 = "[aaa]|bbbb";
        auto result6 = parser.findSegment(input6);
        expect(result6.repeatStartIndex == 1);
        expect(result6.repeatEndIndex == 4);
        expect(result6.releaseBlockIndex == 6);

        beginTest ("Repeat and release (with pre-repeat)");
        String input7 = "aaa[bbb]|cccc";
        auto result7 = parser.findSegment(input7);
        expect(result7.repeatStartIndex == 4);
        expect(result7.repeatEndIndex == 7);
        expect(result7.releaseBlockIndex == 9);

        beginTest ("Empty repeat section");
        String input8 = "aaa[]|cccc";
        auto result8 = parser.findSegment(input8);
        expect(result8.repeatStartIndex == 4);
        expect(result8.repeatEndIndex == 4);
        expect(result8.releaseBlockIndex == 6);

        beginTest ("Empty release section");
        String input9 = "aaa[bbb]|";
        auto result9 = parser.findSegment(input9);
        expect(result9.repeatStartIndex == 4);
        expect(result9.repeatEndIndex == 7);
        expect(result9.releaseBlockIndex == 9);

    }
};
