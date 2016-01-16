/*
  ==============================================================================

    chuGenPolygonPinwheel.cpp
    Created: 16 Jan 2016 1:51:26am
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "chuGenPolygonPinwheel.h"

chuGenPolygonPinwheel::chuGenPolygonPinwheel()
: chuGenerator("PolygonPinwheel")
{
    sides = new chuParameterInt("Sides", 3, 12, 5);
    radius = new chuParameterFloat("Radius", 0.1, 1.0, 1.0);
    copies = new chuParameterInt("Copies", 1, 6, 3);
    scale = new chuParameterFloat("Scale", 0.01, 1.0, 0.618);
    color = new chuParameterColor("Color", Colors::red);
}

void chuGenPolygonPinwheel::getParamList(std::vector<chuParameter*>& params)
{
    chuGenerator::getParamList(params); // call superclass
    
    params.push_back(sides);
    params.push_back(radius);
    params.push_back(copies);
    params.push_back(scale);
    params.push_back(color);
}

std::vector<PatternItem> chuGenPolygonPinwheel::getPatterns(float barClock)
{
    std::vector<PatternItem> items;
    PatternItem item;
    item.type = PatternType::RegularPolygon;
    item.sides = sides->getValue();
    item.radius = radius->getValue();
    item.origin = Vector2f(0, 0);
    item.rotation = barClock * 360;
    item.red = color->getValue().getRed() << 8;
    item.green = color->getValue().getGreen() << 8;
    item.blue = color->getValue().getBlue() << 8;

    int count = 1;
    items.push_back(item);
    while (count++ < copies->getValue())
    {
        item.radius *= scale->getValue();
        item.rotation *= -1;
        items.push_back(item);
    }

    return items;
}