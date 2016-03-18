/*
  ==============================================================================

    chuGenRecolorEffect.cpp
    Created: 17 Mar 2016 9:20:13pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "chuGenRecolorEffect.h"

chuGenRecolorEffect::chuGenRecolorEffect(ValueTree source)
: chuGenerator("RecolorEffect", source)
{
    addParameter(color1 = new chuParameterColor("Color1", Colors::red));
    addParameter(color2 = new chuParameterColor("Color2", Colors::blue));
}

std::vector<PatternItem> chuGenRecolorEffect::getPatterns(float barClock, std::vector<PatternItem>& existingPatterns)
{
    Color c;
    for (int i = 0; i < existingPatterns.size(); i++)
    {
        auto& item = existingPatterns[i];

        c = color1->getValue();
        c = c.interpolatedWith(color2->getValue(), i / (existingPatterns.size() * 1.0));

        item.red = c.getRed() << 8;
        item.green = c.getGreen() << 8;
        item.blue = c.getBlue() << 8;

        for (int j = 0; j < item.polyline.colours.size(); j++)
        {
            auto& ptColor = item.polyline.colours[j];

            c = color1->getValue();
            c = c.interpolatedWith(color2->getValue(), j / (item.polyline.colours.size() * 1.0));
            ptColor = c;
        }
    }
    return existingPatterns;
}