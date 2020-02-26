/*
  ==============================================================================

    TriangleVoice.cpp
    Created: 11 Nov 2019 9:37:04pm
    Author:  除村 武志

  ==============================================================================
*/

#include "TriangleVoice.h"

//---------------------------------------------
//
// Triangle Voice
//
//---------------------------------------------
TriangleVoice::TriangleVoice (SettingRefs* sRefs) : TonalVoice (sRefs) {}

float TriangleVoice::voltageForAngle (double angle)
{
    int sequence[32] = { 1,  2,  3,  4,  5,  6,  7,  8,
                         8,  7,  6,  5,  4,  3,  2,  1,
                         0, -1, -2, -3, -4, -5, -6, -7,
                         -7, -6, -5, -4, -3, -2, -1,  0
                       };

    double twopi = MathConstants<float>::pi * 2.0;
    int step = (int) (32 * angle / twopi);

    int level = sequence[step];
    float output = ((float)level - 0.5f) / 7.5f;
    return output;
}
