/*
  ==============================================================================

    ColorScheme.cpp
    Created: 8 Dec 2019 1:00:26pm
    Author:  除村 武志

  ==============================================================================
*/

#include "ColorScheme.h"

ColorScheme::ColorScheme (ColorSchemeType type)
{
    switch (type)
    {
        case kColorSchemeYmck:
            background = Colour (0xffffffff);
            textBoxFill = Colour (0xfff4f4ff);
            boxFill = Colour (0xff00aeff);
            main = Colour (0xff00aeff);
            mainThinLine = Colour (0xff0086ff);
            mainDarkened = Colour (0xff0080bb);
            accent = Colour (0xffffdd00);
            reversedForeground = Colour (0xffffffff);
            genericBorder = Colour (0xff0080bb);
            warning = Colour (0xffe22be0);
            break;

        case kColorSchemeYmckDark:
            background = Colour (0xff000000);
            textBoxFill = Colour (0xff101010);
            boxFill = Colour (0xff004070);
            main = Colour (0xff00aeff);
            mainThinLine = Colour (0xff40A0ff);
            mainDarkened = Colour (0xff004070);
            accent = Colour (0xffffdd00);
            reversedForeground = Colour (0xffffffff);
            genericBorder = Colour (0xff0080bb);
            warning = Colour (0xffe22be0);
            break;

        case kColorSchemeFamicom:
            background = Colour (0xfff4f5ec);
            boxFill = Colour (0xffead780);
            textBoxFill = Colour (0xfffdfee9);
            main = Colour (0xffc04136);
            mainThinLine = Colour (0xff97372b);
            mainDarkened = Colour (0xffc5b0ae);
            accent = Colour (0xffeed27d);
            reversedForeground = Colour (0xff101010);
            genericBorder = Colour (0xff641c11);
            warning = Colour (0xff641c11);
            break;

        case kColorSchemeNes:
            background = Colour (0xffefefef);
            boxFill = Colour (0xff69616e);
            textBoxFill = Colour (0xffd1c8c3);
            main = Colour (0xff1b1718);
            mainThinLine = Colour (0xff000000);
            mainDarkened = Colour (0xffa1988f);
            accent = Colour (0xffc04136);
            reversedForeground = Colour (0xffffffff);
            genericBorder = Colour (0xffa1988f);
            warning = Colour (0xffc04136);
            break;

        case kColorSchemeMonotoneLight:
            background = Colour (0xffffffff);
            boxFill = Colour (0xffffffff);
            textBoxFill = Colour (0xfff0f0f0);
            main = Colour (0xff202020);
            mainThinLine = Colour (0xff000000);
            mainDarkened = Colour (0xffc0c0c0);
            accent = Colour (0xff808080);
            reversedForeground = Colour (0xff000000);
            genericBorder = Colour (0xff606060);
            warning = Colour (0xff000000);
            break;

        case kColorSchemeMonotoneDark:
            background = Colour (0xff000000);
            boxFill = Colour (0xff101010);
            textBoxFill = Colour (0xff000000);
            main = Colour (0xffffffff);
            mainThinLine = Colour (0xffffffff);
            mainDarkened = Colour (0xff404040);
            accent = Colour (0xffa0a0a0);
            reversedForeground = Colour (0xffffffff);
            genericBorder = Colour (0xffc0c0c0);
            warning = Colour (0xffffffff);
            break;

        default:
            break;
    }
}
