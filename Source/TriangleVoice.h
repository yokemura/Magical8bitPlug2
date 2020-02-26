/*
  ==============================================================================

    TriangleVoice.h
    Created: 11 Nov 2019 9:37:04pm
    Author:  除村 武志

  ==============================================================================
*/

#pragma once
#include "TonalVoice.h"

struct TriangleVoice : public TonalVoice
{
    TriangleVoice (SettingRefs* sRefs);
    float voltageForAngle (double angle) override;
};
