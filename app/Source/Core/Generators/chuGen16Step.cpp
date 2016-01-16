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
    restColor = new chuParameterColor("RestColor", Colors::blue);
    activeColor = new chuParameterColor("ActiveColor", Colors::red);
}

void chuGen16Step::getParamList(std::vector<chuParameter*>& params)
{
    chuGenerator::getParamList(params); // call superclass

    params.push_back(height);
    params.push_back(restColor);
    params.push_back(activeColor);
}

std::vector<PatternItem> chuGen16Step::getPatterns(float barClock)
{
    int step = barClock * 16;

    std::vector<PatternItem> items;
    PatternItem item;
    item.type = PatternType::Polyline;
    item.red = restColor->getValue().getRed() << 8;
    item.green = restColor->getValue().getGreen() << 8;
    item.blue = restColor->getValue().getBlue() << 8;
    item.origin = Vector2f(0, 0);

    item.points.push_back(Vector2f(-1, -height->getValue()));
    if (step > 0)
    {
        item.points.push_back(Vector2f((step - 8)/8.0, -height->getValue()));
    }
    item.points.push_back(Vector2f((step - 8)/8.0, height->getValue()));
    item.points.push_back(Vector2f((step - 7)/8.0, height->getValue()));
    if (step < 15)
    {
        item.points.push_back(Vector2f((step - 7)/8.0, -height->getValue()));
    }
    item.points.push_back(Vector2f(1, -height->getValue()));

    items.push_back(item);
    return items;
}