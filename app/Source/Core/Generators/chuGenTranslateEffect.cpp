/*
  ==============================================================================

    chuGenTranslateEffect.cpp
    Created: 18 Mar 2016 10:43:04am
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "chuGenTranslateEffect.h"

chuGenTranslateEffect::chuGenTranslateEffect(ValueTree source)
: chuGenerator("TranslateEffect", source)
{
    addParameter(manualShiftX = new chuParameterFloat("Shift X", -1.0, 1.0, 0.0));
    addParameter(manualShiftY = new chuParameterFloat("Shift Y", -1.0, 1.0, 0.0));
    addParameter(beatCount1X = new chuParameterInt("X Osc 1 Beats", 1, 4, 0));
    addParameter(beatShift1X = new chuParameterFloat("X Osc 1 Shift", -1.0, 1.0, 0.0));
    addParameter(beatCount2X = new chuParameterInt("X Osc 2 Beats", 1, 4, 0));
    addParameter(beatShift2X = new chuParameterFloat("X Osc 2 Shift", -1.0, 1.0, 0.0));
    addParameter(beatCount1Y = new chuParameterInt("Y Osc 1 Beats", 1, 4, 0));
    addParameter(beatShift1Y = new chuParameterFloat("Y Osc 1 Shift", -1.0, 1.0, 0.0));
    addParameter(beatCount2Y = new chuParameterInt("Y Osc 2 Beats", 1, 4, 0));
    addParameter(beatShift2Y = new chuParameterFloat("Y Osc 2 Shift", -1.0, 1.0, 0.0));
}

void chuGenTranslateEffect::getPatterns(float barClock, std::vector<PatternItem>& patterns)
{
    float xDelta = manualShiftX->getValue() +
                    beatShift1X->getValue() * fmod(barClock * 4.0, beatCount1X->getValue()) +
                    beatShift2X->getValue() * fmod(barClock * 4.0, beatCount2X->getValue());
    float yDelta = manualShiftY->getValue() +
                    beatShift1Y->getValue() * fmod(barClock * 4.0, beatCount1Y->getValue()) +
                    beatShift2Y->getValue() * fmod(barClock * 4.0, beatCount2Y->getValue());

    for (auto& item : patterns) {
        if (item.type == PatternType::Polyline)
        {
            for (auto& pt : item.polyline.vertices)
            {
                pt.x += xDelta;
                pt.y += yDelta;
            }
        }
        else if (item.type == PatternType::RegularPolygon)
        {
            item.origin.x += xDelta;
            item.origin.y += yDelta;
        }
    }
    
}