/*
  ==============================================================================

    FrameSequenceParseErrors.h
    Created: 11 Dec 2019 5:06:52pm
    Author:  除村 武志

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

enum ParseError
{
    kParseErrorNone = 0,
    kParseErrorLevelWarning,
    kParseErrorLevelFatal,
    kParseErrorDuplicatedReleaseDelimiter,
    kParseErrorDuplicatedOpenBracket,
    kParseErrorDuplicatedCloseBracket,
    kParseErrorRepeatingInReleaseBlock,
    kParseErrorUnmatchingOpenBracket,
    kParseErrorUnmatchingCloseBracket,
    kParseErrorUnmatchingBracketNumber,
    kParseErrorMissingSlopeValueDelimiter,
    kParseErrorMissingSlopeLengthDelimiter,
    kParseErrorMissingSlopeInitialValue,
    kParseErrorMissingSlopeFinalValue,
    kParseErrorMissingSlopeFrameCount,
    kParseErrorNotANumber,
    kParseErrorValueOutOfRange,
    kParseErrorFrameLengthTooShort,
    kParseErrorMissingValueForRepeatDelimiter,
    kParseErrorMissingFrameCountForRepeatDelimiter,
};

String getParseErrorString (ParseError err, int minValue = 0, int maxValue = 0);
