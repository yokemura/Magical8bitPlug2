/*
  ==============================================================================

    WaveformVoice.cpp
    Created: 7 Jul 2021 5:57:30am
    Author:  SHACHO

  ==============================================================================
*/

#include "WaveformVoice.h"

//---------------------------------------------
//
// Waveform Voice
//
//---------------------------------------------
WaveformVoice::WaveformVoice(SettingRefs* sRefs) : TonalVoice(sRefs) {}

float WaveformVoice::voltageForAngle(double angle)
{
    int x = settingRefs->getWaveformX();
    int y = 63; // settingRefs->getWaveformY();

    float sequence[64];

    for (int i = 0; i < x; i++)
    {
        sequence[i] = *(settingRefs->waveformWave[i]);
    }

    double twopi = MathConstants<float>::pi * 2.0;
    int step = (int)(x * angle / twopi);

    float level = sequence[step];
    float output = (float)level / (y / 2.0f) - 1.0f;

    return output;
}
