/*
  ==============================================================================

    chuGenerator.cpp
    Created: 30 Dec 2015 1:32:56pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "chuGenerator.h"


GeneratorParameterFloat::GeneratorParameterFloat(String _name, float _min, float _max, float _defaultValue)
: name(_name), minValue(_min), maxValue(_max), defaultValue(_defaultValue), value(_defaultValue)
{
}

chuGenPolygonPinwheel::chuGenPolygonPinwheel()
: chuGenerator("PolygonPinwheel")
{
    sides = new GeneratorParameterFloat("Sides", 3.0, 8.0, 5.0);
    radius = new GeneratorParameterFloat("Radius", 0.1, 1.0, 1.0);
    copies = new GeneratorParameterFloat("Copies", 1.0, 5.0, 3.0);
}

void chuGenPolygonPinwheel::getParams(std::vector<GeneratorParameterFloat*>& params)
{
    chuGenerator::getParams(params); // call superclass
    
    params.push_back(sides);
    params.push_back(radius);
    params.push_back(copies);
}

std::vector<PatternItem> chuGenPolygonPinwheel::getPatterns()
{
    std::vector<PatternItem> items;
    PatternItem item;
    item.type = PatternType::RegularPolygon;
    item.sides = sides->value;
    item.radius = radius->value;
    item.origin = Vector2f(0, 0);
    item.rotation = Time::getMillisecondCounterHiRes() * 180/1200.0;

    int count = 1;
    items.push_back(item);
    while (count++ < copies->value)
    {
        item.radius *= 1 - 1 / copies->value;
        item.rotation *= -1;
        items.push_back(item);
    }

    return items;
}

std::vector<PatternItem> chuGenTenPoints::getPatterns()
{
    std::vector<PatternItem> items;
    return items;
}

std::vector<PatternItem> chuGenSpirograph::getPatterns()
{
    std::vector<PatternItem> items;
    return items;
}