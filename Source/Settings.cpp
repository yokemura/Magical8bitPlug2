/*
  ==============================================================================

    Settings.cpp
    Created: 23 May 2019 11:54:44am
    Author:  除村 武志

  ==============================================================================
*/

#include "Settings.h"
#include "FrameSequenceParser.h"

bool SettingRefs::setSequenceWithString (const String& type, const String& input, ParseError* error)
{
    FrameSequenceParser parser;

    if (type == "volume")
    {
        FrameSequence res = parser.parse (input, 0, 15, error);

        if (*error > kParseErrorLevelFatal)
        {
            return false;
        }

        volumeSequence = res;
        volumeSequenceString = input;
        return true;
    }
    else if (type == "pitch")
    {
        FrameSequence res = parser.parse (input, -64, 63, error);

        if (*error > kParseErrorLevelFatal)
        {
            return false;
        }

        pitchSequence = res;
        pitchSequenceString = input;
        return true;
    }
    else if (type == "duty")
    {
        FrameSequence res = parser.parse (input, 0, 2, error);

        if (*error > kParseErrorLevelFatal)
        {
            return false;
        }

        dutySequence = res;
        dutySequenceString = input;
        return true;
    }

    printf ("*** parameter type invalid!\n");
    return false;
}

String& SettingRefs::getSequenceString (const String& type)
{
    if (type == "volume")
    {
        return volumeSequenceString;
    }
    else if (type == "pitch")
    {
        return pitchSequenceString;
    }
    else if (type == "duty")
    {
        return dutySequenceString;
    }

    printf ("*** parameter type invalid!\n");
    return volumeSequenceString;
}

//void SettingRefs::setWaveform(AudioProcessorValueTreeState* parameters)
//{
//    // waveform
//    for (int i = 0; i < 64; i++)
//    {
//        waveformWave[i] = (float*)parameters->getRawParameterValue("waveformWave" + String(i));
//    }
//    waveformX = (float*)parameters->getRawParameterValue("waveformX");
//    waveformY = (float*)parameters->getRawParameterValue("waveformY");
//    waveformTemplate = (float*)parameters->getRawParameterValue("waveformTemplate");
//}

int SettingRefs::getWaveformX()
{
    int range[3] = {16, 32, 64};

    return range[(int)(*waveformX)];
}

int SettingRefs::getWaveformY()
{
    int range[3] = { 16, 32, 64 };

    return range[(int)(*waveformY)] - 1;
}
