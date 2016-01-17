/*
  ==============================================================================

    chuGen16Step.cpp
    Created: 16 Jan 2016 1:52:05am
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "chuGen16Step.h"

chuGen16Step::chuGen16Step()
: chuGenerator("16Step")
{
    height = new chuParameterFloat("Height", 0.01, 1.0, 0.3);
    numSteps = new chuParameterInt("Steps", 2, 16, 16);
    restColor = new chuParameterColor("RestColor", Colors::blue);
    activeColor = new chuParameterColor("ActiveColor", Colors::red);
}

void chuGen16Step::getParamList(std::vector<chuParameter*>& params)
{
    chuGenerator::getParamList(params); // call superclass

    params.push_back(height);
    params.push_back(numSteps);
    params.push_back(restColor);
    params.push_back(activeColor);
}

std::vector<PatternItem> chuGen16Step::getPatterns(float barClock)
{
    int count = numSteps->getValue();
    int step = (int)(count * barClock) % count;
    float stepScaled = step/(count * 0.5) - 1.0;
    float barWidth = 2.0 /(count * 1.0);

    std::vector<PatternItem> items;
    PatternItem item;
    item.type = PatternType::Polyline;
    item.red = restColor->getValue().getRed() << 8;
    item.green = restColor->getValue().getGreen() << 8;
    item.blue = restColor->getValue().getBlue() << 8;
    item.origin = Vector2f(0, 0);

    item.polyline.addPoint(Vector2f(-1, -height->getValue()), restColor->getValue());
    if (step > 0)
    {
        item.polyline.addPoint(Vector2f(stepScaled, -height->getValue()), restColor->getValue());
    }
    item.polyline.addPoint(Vector2f(stepScaled, height->getValue()), activeColor->getValue());
    item.polyline.addPoint(Vector2f(stepScaled + barWidth, height->getValue()), activeColor->getValue());
    if (step < 15)
    {
        item.polyline.addPoint(Vector2f(stepScaled + barWidth, -height->getValue()), restColor->getValue());
    }
    item.polyline.addPoint(Vector2f(1, -height->getValue()), restColor->getValue());

    items.push_back(item);
    return items;
}