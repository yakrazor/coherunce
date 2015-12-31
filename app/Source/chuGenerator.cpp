/*
  ==============================================================================

    chuGenerator.cpp
    Created: 30 Dec 2015 1:32:56pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "chuGenerator.h"
#include "chuOSCManager.h"


GeneratorParameterFloat::GeneratorParameterFloat(String _name, float _min, float _max, float _defaultValue,
                                                 bool _userVisible)
: name(_name), minValue(_min), maxValue(_max), defaultValue(_defaultValue), value(_defaultValue), userVisible(_userVisible)
{
}

void GeneratorParameterFloat::oscMessageReceived(const OSCMessage& message)
{
    OSCArgument* arg = message.begin();
    if (arg && arg->isFloat32())
    {
        value = arg->getFloat32();
    }
    else if (arg && arg->isInt32())
    {
        value = (float)arg->getInt32();
    }
}

void chuGenerator::setOSCAddress(const String& addr)
{
    std::vector<GeneratorParameterFloat*> params;
    getParams(params);
    for (auto& param : params)
    {
        if (chuOSCManager::getReceiver())
        {
            chuOSCManager::getReceiver()->removeListener(param);
            chuOSCManager::getReceiver()->addListener(param, addr + "/param/" + param->name);
        }
    }
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

chuGenFivePoints::chuGenFivePoints()
: chuGenerator("FivePoints")
{
    sides = new GeneratorParameterFloat("Sides", 3.0, 8.0, 3.0);
    radius = new GeneratorParameterFloat("Radius", 0.1, 1.0, 0.15);

    pt1x  = new GeneratorParameterFloat("pt1x",  leapXMin, leapXMax, 0.0, false);
    pt1y  = new GeneratorParameterFloat("pt1y",  leapYMin, leapYMax, 0.0, false);
    pt1on = new GeneratorParameterFloat("pt1on", 0.0, 1.0, 0.0, false);
    pt2x  = new GeneratorParameterFloat("pt2x",  leapXMin, leapXMax, 0.0, false);
    pt2y  = new GeneratorParameterFloat("pt2y",  leapYMin, leapYMax, 0.0, false);
    pt2on = new GeneratorParameterFloat("pt2on", 0.0, 1.0, 0.0, false);
    pt3x  = new GeneratorParameterFloat("pt3x",  leapXMin, leapXMax, 0.0, false);
    pt3y  = new GeneratorParameterFloat("pt3y",  leapYMin, leapYMax, 0.0, false);
    pt3on = new GeneratorParameterFloat("pt3on", 0.0, 1.0, 0.0, false);
    pt4x  = new GeneratorParameterFloat("pt4x",  leapXMin, leapXMax, 0.0, false);
    pt4y  = new GeneratorParameterFloat("pt4y",  leapYMin, leapYMax, 0.0, false);
    pt4on = new GeneratorParameterFloat("pt4on", 0.0, 1.0, 0.0, false);
    pt5x  = new GeneratorParameterFloat("pt5x",  leapXMin, leapXMax, 0.0, false);
    pt5y  = new GeneratorParameterFloat("pt5y",  leapYMin, leapYMax, 0.0, false);
    pt5on = new GeneratorParameterFloat("pt5on", 0.0, 1.0, 0.0, false);
}

void chuGenFivePoints::getParams(std::vector<GeneratorParameterFloat*>& params)
{
    chuGenerator::getParams(params); // call superclass

    params.push_back(sides);
    params.push_back(radius);
    params.push_back(pt1x);
    params.push_back(pt1y);
    params.push_back(pt1on);
    params.push_back(pt2x);
    params.push_back(pt2y);
    params.push_back(pt2on);
    params.push_back(pt3x);
    params.push_back(pt3y);
    params.push_back(pt3on);
    params.push_back(pt4x);
    params.push_back(pt4y);
    params.push_back(pt4on);
    params.push_back(pt5x);
    params.push_back(pt5y);
    params.push_back(pt5on);
}

inline float rescale(float value, float inputMin, float inputMax, float outputMin, float outputMax)
{
    float s = (value - inputMin) / (inputMax - inputMin);
    return outputMin + s * outputMax;
}

std::vector<PatternItem> chuGenFivePoints::getPatterns()
{
    PatternItem item;
    item.type = PatternType::RegularPolygon;
    item.sides = sides->value;
    item.radius = radius->value;
    item.rotation = Time::getMillisecondCounterHiRes() * 180/800.0;

    std::vector<PatternItem> items;
    if (pt1on->value)
    {
        item.origin.x = rescale(pt1x->value, leapXMin, leapXMax, -1.25, 1.25);
        item.origin.y = rescale(pt1y->value, leapYMin, leapYMax, -1.25, 1.25);
        items.push_back(item);
    }
    if (pt2on->value)
    {
        item.origin.x = rescale(pt2x->value, leapXMin, leapXMax, -1.25, 1.25);
        item.origin.y = rescale(pt2y->value, leapYMin, leapYMax, -1.25, 1.25);
        items.push_back(item);
    }
    if (pt3on->value)
    {
        item.origin.x = rescale(pt3x->value, leapXMin, leapXMax, -1.25, 1.25);
        item.origin.y = rescale(pt3y->value, leapYMin, leapYMax, -1.25, 1.25);
        items.push_back(item);
    }
    if (pt4on->value)
    {
        item.origin.x = rescale(pt4x->value, leapXMin, leapXMax, -1.25, 1.25);
        item.origin.y = rescale(pt4y->value, leapYMin, leapYMax, -1.25, 1.25);
        items.push_back(item);
    }
    if (pt5on->value)
    {
        item.origin.x = rescale(pt5x->value, leapXMin, leapXMax, -1.25, 1.25);
        item.origin.y = rescale(pt5y->value, leapYMin, leapYMax, -1.25, 1.25);
        items.push_back(item);
    }
    return items;
}

std::vector<PatternItem> chuGenSpirograph::getPatterns()
{
    std::vector<PatternItem> items;
    return items;
}