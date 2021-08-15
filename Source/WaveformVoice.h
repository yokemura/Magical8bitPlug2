/*
  ==============================================================================

    WaveformVoice.h
    Created: 7 Jul 2021 5:57:30am
    Author:  SHACHO

  ==============================================================================
*/

#pragma once
#include "TonalVoice.h"

struct WaveformVoice : public TonalVoice
{
    WaveformVoice(SettingRefs* sRefs);
    float voltageForAngle(double angle) override;
};
