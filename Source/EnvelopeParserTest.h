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
        
        //-------------------------------------------------------
        //
        // Section index
        //
        //-------------------------------------------------------
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

        beginTest ("[Error] Multiple open bracket");
        String input10 = "aaa[[bbb]";
        auto result10 = parser.findSegment(input10);
        expect(result10.error = kParseErrorDuplicatedOpenBracket);

        beginTest ("[Error] Multiple close bracket");
        String input11 = "aaa[bbb]]";
        auto result11 = parser.findSegment(input11);
        expect(result11.error = kParseErrorDuplicatedCloseBracket);

        beginTest ("[Error] Unmatching close bracket");
        String input12 = "aaabbb]";
        auto result12 = parser.findSegment(input12);
        expect(result12.error = kParseErrorUnmatchingCloseBracket);

        beginTest ("[Error] Repeat in release segment");
        String input13 = "aaa|[bbb]";
        auto result13 = parser.findSegment(input13);
        expect(result13.error = kParseErrorRepeatingInReleaseBlock);
        
        //-------------------------------------------------------
        //
        // Slope
        //
        //-------------------------------------------------------
        ParseError error = kParseErrorNone;
        
        beginTest ("Down slope");
        String input14 = "3to0in4";
        std::vector<int> result14 = parser.parseSlope(input14, 0, 15, &error);
        expect(result14.size() == 4);
        expect(result14[0] == 3);
        expect(result14[1] == 2);
        expect(result14[2] == 1);
        expect(result14[3] == 0); // Should include the last value

        beginTest ("Slow decrement");
        String input15 = "2to0in8";
        std::vector<int> result15 = parser.parseSlope(input15, 0, 15, &error);
        expect(result15.size() == 8);
        expect(result15[0] == 2);
        expect(result15[1] == 2);
        expect(result15[2] == 1);
        expect(result15[3] == 1);
        expect(result15[4] == 1);
        expect(result15[5] == 1);
        expect(result15[6] == 0);
        expect(result15[7] == 0);

        beginTest ("Fast decrement");
        String input16 = "15to0in5";
        std::vector<int> result16 = parser.parseSlope(input16, 0, 15, &error);
        expect(result16.size() == 5);
        expect(result16[0] == 15);
        expect(result16[1] == 11);
        expect(result16[2] == 8);
        expect(result16[3] == 4);
        expect(result16[4] == 0);

        beginTest ("Up slope");
        String input17 = "0to3in4";
        std::vector<int> result17 = parser.parseSlope(input17, 0, 15, &error);
        expect(result17.size() == 4);
        expect(result17[0] == 0);
        expect(result17[1] == 1);
        expect(result17[2] == 2);
        expect(result17[3] == 3); // Should include the last value

        beginTest ("[Error] Missing 'in'");
        String input18 = "0to3";
        std::vector<int> result18 = parser.parseSlope(input18, 0, 15, &error);
        expect(error == kParseErrorMissingSlopeLengthDelimiter);

        beginTest ("[Error] Missing initial value");
        String input19 = "to5in5";
        std::vector<int> result19 = parser.parseSlope(input19, 0, 15, &error);
        expect(error == kParseErrorMissingSlopeInitialValue);

        beginTest ("[Error] Missing final value");
        String input20 = "4toin5";
        std::vector<int> result20 = parser.parseSlope(input20, 0, 15, &error);
        expect(error == kParseErrorMissingSlopeFinalValue);

        beginTest ("[Error] Missing frame count");
        String input21 = "0to3in";
        std::vector<int> result21 = parser.parseSlope(input21, 0, 15, &error);
        expect(error == kParseErrorMissingSlopeFrameCount);

        //-------------------------------------------------------
        //
        // Hold
        //
        //-------------------------------------------------------
        beginTest ("Hold");
        String input22 = "15x3";
        std::vector<int> result22 = parser.parseHold(input22, 0, 15, &error);
        expect(result22.size() == 3);
        expect(result22[0] == 15);
        expect(result22[1] == 15);
        expect(result22[2] == 15);

        beginTest ("[Error] Missing value");
        String input23 = "x3";
        std::vector<int> result23 = parser.parseHold(input23, 0, 15, &error);
        expect(error == kParseErrorMissingHoldValue);

        beginTest ("[Error] Missing value");
        String input24 = "3x";
        std::vector<int> result24 = parser.parseHold(input24, 0, 15, &error);
        expect(error == kParseErrorMissingHoldFrameCount);

        //-------------------------------------------------------
        //
        // Total
        //
        //-------------------------------------------------------

    }
};
