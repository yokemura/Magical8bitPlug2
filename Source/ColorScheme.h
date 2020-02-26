/*
  ==============================================================================

    ColorScheme.h
    Created: 8 Dec 2019 1:00:26pm
    Author:  除村 武志

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

enum ColorSchemeType
{
    kColorSchemeYmck = 0,
    kColorSchemeYmckDark,
    kColorSchemeFamicom,
    kColorSchemeNes,
    kColorSchemeMonotoneLight,
    kColorSchemeMonotoneDark
};

struct ColorScheme
{
    Colour background;
    Colour boxFill;
    Colour textBoxFill;
    Colour main;
    Colour mainThinLine;
    Colour mainDarkened;
    Colour accent;
    Colour reversedForeground;
    Colour genericBorder;
    Colour warning;

    ColorScheme (ColorSchemeType type);
};
