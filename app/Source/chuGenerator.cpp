/*
  ==============================================================================

    chuGenerator.cpp
    Created: 30 Dec 2015 1:32:56pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "chuGenerator.h"
#include "chuOSCManager.h"




chuGenerator::chuGenerator(String generatorName) : name(generatorName), active(false)
{
    init();
};

void chuGenerator::setOSCAddress(const String& addr)
{
    std::vector<chuParameter*> params;
    getParamList(params);
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
    sides = new chuParameterFloat("Sides", 3.0, 8.0, 5.0);
    radius = new chuParameterFloat("Radius", 0.1, 1.0, 1.0);
    copies = new chuParameterFloat("Copies", 1.0, 5.0, 3.0);
}

void chuGenPolygonPinwheel::getParamList(std::vector<chuParameter*>& params)
{
    chuGenerator::getParamList(params); // call superclass
    
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
    sides = new chuParameterFloat("Sides", 3.0, 8.0, 3.0);
    radius = new chuParameterFloat("Radius", 0.01, 0.1, 0.08);

    red = new chuParameterFloat("red", 0.0, 1.0, 1.0);
    green = new chuParameterFloat("green", 0.0, 1.0, 0.0);
    blue = new chuParameterFloat("blue", 0.0, 1.0, 0.0);

    chuParameterOptions options;
    options.isUserVisible = false;

    pt1x  = new chuParameterFloat("pt1x",  leapXMin, leapXMax, 0.0, options);
    pt1y  = new chuParameterFloat("pt1y",  leapYMin, leapYMax, 0.0, options);
    pt1on = new chuParameterFloat("pt1on", 0.0, 1.0, 0.0, options);
    pt2x  = new chuParameterFloat("pt2x",  leapXMin, leapXMax, 0.0, options);
    pt2y  = new chuParameterFloat("pt2y",  leapYMin, leapYMax, 0.0, options);
    pt2on = new chuParameterFloat("pt2on", 0.0, 1.0, 0.0, options);
    pt3x  = new chuParameterFloat("pt3x",  leapXMin, leapXMax, 0.0, options);
    pt3y  = new chuParameterFloat("pt3y",  leapYMin, leapYMax, 0.0, options);
    pt3on = new chuParameterFloat("pt3on", 0.0, 1.0, 0.0, options);
    pt4x  = new chuParameterFloat("pt4x",  leapXMin, leapXMax, 0.0, options);
    pt4y  = new chuParameterFloat("pt4y",  leapYMin, leapYMax, 0.0, options);
    pt4on = new chuParameterFloat("pt4on", 0.0, 1.0, 0.0, options);
    pt5x  = new chuParameterFloat("pt5x",  leapXMin, leapXMax, 0.0, options);
    pt5y  = new chuParameterFloat("pt5y",  leapYMin, leapYMax, 0.0, options);
    pt5on = new chuParameterFloat("pt5on", 0.0, 1.0, 0.0, options);
}

void chuGenFivePoints::getParamList(std::vector<chuParameter*>& params)
{
    chuGenerator::getParamList(params); // call superclass

    params.push_back(sides);
    params.push_back(radius);
    params.push_back(red);
    params.push_back(green);
    params.push_back(blue);
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
    return outputMin + s * (outputMax - outputMin);
}

std::vector<PatternItem> chuGenFivePoints::getPatterns()
{
    PatternItem item;
    item.type = PatternType::RegularPolygon;
    item.sides = sides->value;
    item.radius = radius->value;
    item.rotation = Time::getMillisecondCounterHiRes() * 180/800.0;
    item.red = 65535 * red->value;
    item.green = 65535 * green->value;
    item.blue = 65535 * blue->value;

    std::vector<PatternItem> items;
    if (pt1on->value)
    {
        item.origin.x = rescale(pt1x->value, leapXMin, leapXMax, -1.0, 1.0);
        item.origin.y = rescale(pt1y->value, leapYMin, leapYMax, -1.0, 1.0);
        items.push_back(item);
    }
    if (pt2on->value)
    {
        item.origin.x = rescale(pt2x->value, leapXMin, leapXMax, -1.0, 1.0);
        item.origin.y = rescale(pt2y->value, leapYMin, leapYMax, -1.0, 1.0);
        items.push_back(item);
    }
    if (pt3on->value)
    {
        item.origin.x = rescale(pt3x->value, leapXMin, leapXMax, -1.0, 1.0);
        item.origin.y = rescale(pt3y->value, leapYMin, leapYMax, -1.0, 1.0);
        items.push_back(item);
    }
    if (pt4on->value)
    {
        item.origin.x = rescale(pt4x->value, leapXMin, leapXMax, -1.0, 1.0);
        item.origin.y = rescale(pt4y->value, leapYMin, leapYMax, -1.0, 1.0);
        items.push_back(item);
    }
    if (pt5on->value)
    {
        item.origin.x = rescale(pt5x->value, leapXMin, leapXMax, -1.0, 1.0);
        item.origin.y = rescale(pt5y->value, leapYMin, leapYMax, -1.0, 1.0);
        items.push_back(item);
    }
    return items;
}

std::vector<PatternItem> chuGenSpirograph::getPatterns()
{
    std::vector<PatternItem> items;
    return items;
}