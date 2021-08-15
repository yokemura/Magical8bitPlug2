/*
  ==============================================================================

    FrameSequenceParser.cpp
    Created: 11 Dec 2019 8:49:02am
    Author:  除村 武志

  ==============================================================================
*/

#include "FrameSequenceParser.h"

std::vector<int> FrameSequenceParser::parseSlope (const String& input,
                             int minValue,
                             int maxValue,
                             ParseError* error)
{
    std::vector<int> retval;

    // find index of "to"
    int toIndex = input.indexOf ("to");

    if (toIndex < 0)
    {
        // Normally this is impossible because it's checking existance of "to" to check if it's a slope
        *error = kParseErrorMissingSlopeValueDelimiter;
        return retval;
    }

    if (toIndex < 1)
    {
        *error = kParseErrorMissingSlopeInitialValue;
        return retval;
    }

    // find index of "in"
    int inIndex = input.indexOf ("in");

    if (inIndex < 0)
    {
        *error = kParseErrorMissingSlopeLengthDelimiter;
        return retval;
    }

    if (inIndex > input.length() - 3)
    {
        *error = kParseErrorMissingSlopeFrameCount;
        return retval;
    }
    if (inIndex - toIndex < 3)
    {
        *error = kParseErrorMissingSlopeFinalValue;
        return retval;
    }

    // get 3 substrings separated by "to" and "in" and put them into `from`, `to`, `cntStr`
    String fromStr = input.substring (0, toIndex);
    String toStr = input.substring (toIndex + 2, inIndex);
    String cntStr = input.substring (inIndex + 2, input.length());


    // remove "f" from `cntStr` if exists
    String cntStr_t = cntStr.replace ("f", "");

    if (!fromStr.containsOnly ("-0123456789"))
    {
        *error = kParseErrorNotANumber;
        return retval;
    }

    if (!toStr.containsOnly ("-0123456789"))
    {
        *error = kParseErrorNotANumber;
        return retval;
    }

    if (!cntStr_t.containsOnly ("-0123456789"))
    {
        *error = kParseErrorNotANumber;
        return retval;
    }

    // convert each strings to int
    double fromValue = fromStr.getDoubleValue();
    double toValue = toStr.getDoubleValue();
    double cntValue = cntStr_t.getDoubleValue();

    if (fromValue > (double)maxValue || toValue > (double)maxValue )
    {
        *error = kParseErrorValueOutOfRange;
        return retval;
    }

    if (fromValue < (double)minValue || toValue < (double)minValue )
    {
        *error = kParseErrorValueOutOfRange;
        return retval;
    }

    if (cntValue < 2.0)
    {
        *error = kParseErrorFrameLengthTooShort;
        return retval;
    }

    // calculate slope as double
    double slope = (toValue - fromValue) / (cntValue - 1.0);

    for (double i = 0; i < cntValue; i += 1.0)
    {
        double value = fromValue + slope * i;
        int rounded = round (value);
        retval.push_back (rounded);
    }

    return retval;
}

std::vector<int> FrameSequenceParser::parseHold (const String& input,
                              int minValue,
                              int maxValue,
                              ParseError* error)
{
    std::vector<int> retval;
    // find index of "x"
    int xIndex = input.indexOf ("x");

    if (xIndex < 1)
    {
        *error = kParseErrorMissingHoldValue;
        return retval;
    }

    if (xIndex >= input.length() - 1)
    {
        *error = kParseErrorMissingHoldFrameCount;
        return retval;
    }

    // separate into value, count
    String valueStr = input.substring (0, xIndex);
    String cntStr = input.substring (xIndex + 1, input.length());
    // remove "f" from `cntStr` if exists
    String cntStr_t = cntStr.replace ("f", "");

    if (!valueStr.containsOnly ("-0123456789"))
    {
        *error = kParseErrorNotANumber;
        return retval;
    }

    if (!cntStr_t.containsOnly ("-0123456789"))
    {
        *error = kParseErrorNotANumber;
        return retval;
    }

    int value = valueStr.getIntValue();

    if (value < minValue || value > maxValue)
    {
        *error = kParseErrorValueOutOfRange;
        return retval;
    }

    int count = cntStr_t.getIntValue();

    for (int i = 0; i < count; i++)
    {
        retval.push_back (value);
    }

    return retval;
}

std::vector<int> FrameSequenceParser::parseSegment (const String& input,
                               int minValue,
                               int maxValue,
                               ParseError* error)
{
    std::vector<int> retval;

    StringArray temp;
    temp.addTokens (input, ",", "");

    for (String aToken : temp)
    {
        std::vector<int> parsed;

        if (aToken.contains ("to"))
        {
            // parse as slope
            parsed = parseSlope (aToken, minValue, maxValue, error);
        }
        else if (aToken.contains ("x"))
        {
            // parse as repeat-fixed-value
            parsed = parseHold (aToken, minValue, maxValue, error);
        }
        else
        {
            // parse as single value
            if (aToken.length() < 1)
            {
                *error = kParseErrorNotANumber;
                return retval;
            }

            if (!aToken.containsOnly ("-0123456789"))
            {
                *error = kParseErrorNotANumber;
                return retval;
            }

            int value = aToken.getIntValue();

            if (value < minValue || value > maxValue)
            {
                *error = kParseErrorValueOutOfRange;
                return retval;
            }

            parsed.push_back (value);
        }

        retval.insert (retval.end(), parsed.begin(), parsed.end());
    }

    return retval;
}

SegmentIndexes FrameSequenceParser::findSegment(const String& input) {
    int releaseBlockIndex = -1;
    int repeatStartIndex = -1;
    int repeatEndIndex = -1;
    int openBracketCount = 0;
    int closeBracketCount = 0;

    SegmentIndexes retval = SegmentIndexes();

    // loop by character
    for (int i = 0; i < input.length(); i++)
    {
        if (input[i] == '|')  // found "|":
        {
            if (releaseBlockIndex >= 0)
            {
                //   if releaseBlockIndex is already determined: Duplication Error
                retval.error = kParseErrorDuplicatedReleaseDelimiter;
                return retval;
            }

            //            if(repeatStartIndex >= 0) {
            //                //   if appeard before "[" or  "]": Repetition After Release Error
            //                throw new FrameSequenceParseException(TRANS("You cannot repeat in release phase"), true);
            //            }
            //   set releaseBlockIndex
            releaseBlockIndex = i + 1;

            if (repeatEndIndex < 0)
            {
                // if "]" is omitted: Also set repeatEndIndex
                repeatEndIndex = i;
            }
        }

        if (input[i] == '[')  /// found "[":
        {
            openBracketCount++;

            if (openBracketCount > 1)
            {
                //   Duplication Error
                retval.error = kParseErrorDuplicatedOpenBracket;
                return retval;
            }

            if (releaseBlockIndex >= 0)
            {
                //   if repeat end is already defined: Repetition After Release Error
                retval.error = kParseErrorRepeatingInReleaseBlock;
                return retval;
            }

            if (repeatEndIndex >= 0)
            {
                //   if repeat end is already defined: Repetition After Release Error
                retval.error = kParseErrorDuplicatedOpenBracket;
                return retval;
            }

            //   set repeatStartIndex
            repeatStartIndex = i + 1;
        }

        if (input[i] == ']')  // found "]":
        {
            closeBracketCount++;

            if (closeBracketCount > 1)
            {
                //    Duplication Error
                retval.error = kParseErrorDuplicatedCloseBracket;
                return retval;
            }

            if (repeatStartIndex < 0)
            {
                //   if repeatStartIndex hasn't set: Syntax Error
                retval.error = kParseErrorUnmatchingCloseBracket;
                return retval;
            }

            if (releaseBlockIndex >= 0)
            {
                //   if repeat end is already defined: Repetition After Release Error
                retval.error = kParseErrorRepeatingInReleaseBlock;
                return retval;
            }

            repeatEndIndex = i;
        }
    }

    //    if (releaseBlockIndex < 0) { // "|" didn't explicitly specified
    //        releaseBlockIndex = trimmed.length();
    //    }

    if (openBracketCount != closeBracketCount)
    {
        retval.error = kParseErrorUnmatchingBracketNumber;
        return retval;
    }

    if (releaseBlockIndex - repeatEndIndex > 1)
    {
        //        throw new FrameSequenceParseException(TRANS("Elements between repeat block and release block will be ignored"), false);
        // FiXME: non-fatal exceptionをどう扱うか
    }

    retval.releaseBlockIndex = releaseBlockIndex;
    retval.repeatStartIndex = repeatStartIndex;
    retval.repeatEndIndex = repeatEndIndex;
    return retval;
}

void FrameSequenceParser::splitSegment (const String& input,
                                        SegmentIndexes indexes,
                                        String& beforeRepeat,
                                        String& insideRepeat,
                                        String& afterRelease) {
    int releaseBlockIndex = indexes.releaseBlockIndex;
    int repeatStartIndex = indexes.repeatStartIndex;
    int repeatEndIndex = indexes.repeatEndIndex;

    // Just for convenience
    bool hasRelease = (releaseBlockIndex >= 0);
    bool shouldRepeat = (repeatStartIndex >= 0);

    if (shouldRepeat)
    {
        if (hasRelease)
        {
            beforeRepeat = input.substring(0, repeatStartIndex - 1);
            insideRepeat = input.substring (repeatStartIndex, repeatEndIndex);
            afterRelease = input.substring(releaseBlockIndex, input.length());
        }
        else
        {
            beforeRepeat = input.substring(0, repeatStartIndex - 1);
            insideRepeat = input.substring (repeatStartIndex, repeatEndIndex);
        }
    }
    else
    {
        if (hasRelease) {
            beforeRepeat = input.substring (0, releaseBlockIndex - 1);
            afterRelease = input.substring (releaseBlockIndex, input.length());
        }
        else
        {
            beforeRepeat = input.substring (0, input.length());
        }
    }
}

FrameSequence FrameSequenceParser::parse (const String& input,
                                          int minValue,
                                          int maxValue,
                                          ParseError* error)
{

    FrameSequence fs;

    //-----------------------------------
    //
    // Preprocessing
    //
    //-----------------------------------

    // Remove white spaces
    String trimmed = input.replace (" ", "");

    //
    // Overall structure
    //
    SegmentIndexes si = findSegment(trimmed);

    // Just for convenience
    bool hasRelease = (si.releaseBlockIndex >= 0);
    bool shouldRepeat = (si.repeatStartIndex >= 0);

    //-----------------------------------
    //
    // Split segments
    //
    //-----------------------------------

    String str_beforeRepeat;
    String str_insideRepeat;
    String str_release;

    splitSegment(trimmed, si, str_beforeRepeat, str_insideRepeat, str_release);

    //-----------------------------------
    //
    // Parse segments
    //
    //-----------------------------------

    // Parse main segment to get frameSequence
    // And set frameSequence value to working variable
    //    FrameSequence *fs = std::make_unique<FrameSequence>();

    std::vector<int> sequence = parseSegment (str_beforeRepeat, minValue, maxValue, error);

    if (*error > kParseErrorLevelFatal)
    {
        return fs;
    }
    if (sequence.size() == 0) {
        *error = kParseWarningPreRepeatSegmentEmpty;
    }

    fs.sequence = sequence;
    fs.sequence.reserve (1000);
    fs.releaseSequenceStartIndex = (int)fs.sequence.size();

    if (shouldRepeat)  // If repeat segment exists:
    {
        //   Set repeatStartIndex according to current working frameSequence length
        fs.isLooped = true;
        fs.loopStartIndex = (int)fs.sequence.size();

        //   Parse repeat segment and to get frameSequence
        std::vector<int> repeatSeq = parseSegment (str_insideRepeat, minValue, maxValue, error);

        if (*error > kParseErrorLevelFatal)
        {
            return fs;
        }
        if (repeatSeq.size() == 0) {
            // Repeat section is defined but content is empty
            *error = kParseWarningRepeatSegmentEmpty;
        }

        //   Add the result to working frameSequence
        fs.sequence.insert (fs.sequence.end(), repeatSeq.begin(), repeatSeq.end());

        //   Set repeatEndIndex according to current working frameSequence length
        fs.releaseSequenceStartIndex = (int)fs.sequence.size();
    }

    if (hasRelease)  // If release exists:
    {
        //   Set releaseStartIndex according to current working frameSequence length
        fs.releaseSequenceStartIndex = (int)fs.sequence.size();
        fs.hasRelease = true;

        //   Parse release segment to get frameSequence
        std::vector<int> releaseSeq = parseSegment (str_release, minValue, maxValue, error);

        if (*error > kParseErrorLevelFatal)
        {
            return fs;
        }
        if (releaseSeq.size() == 0) {
            // Release section is defined but content is empty
            *error = kParseWarningRepeatSegmentEmpty;
        }

        //   Add the result to working frameSequence
        fs.sequence.insert (fs.sequence.end(), releaseSeq.begin(), releaseSeq.end());
        printf ("success");
    }

    // return the frameSequence
    return fs;
}
