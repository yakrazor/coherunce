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
            chuOSCManager::getReceiver()->addListener(param, addr + "/param/" + param->getName());
        }
    }
}

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

chuGenFivePoints::chuGenFivePoints()
: chuGenerator("FivePoints")
{
    sides = new chuParameterInt("Sides", 3, 8, 3);
    radius = new chuParameterFloat("Radius", 0.01, 0.1, 0.08);

    color = new chuParameterColor("Color", Colors::red);

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
    params.push_back(color);
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

std::vector<PatternItem> chuGenFivePoints::getPatterns(float barClock)
{
    PatternItem item;
    item.type = PatternType::RegularPolygon;
    item.sides = sides->getValue();
    item.radius = radius->getValue();
    item.rotation = barClock * 360;
    item.red = color->getValue().getRed() << 8;
    item.green = color->getValue().getGreen() << 8;
    item.blue = color->getValue().getBlue() << 8;

    bool flipX = false;
    float laserXMin = flipX ? 1.0 : -1.0;
    float laserXMax = flipX ? -1.0 : 1.0;
    bool flipY = true;
    float laserYMin = flipY ? 1.0 : -1.0;
    float laserYMax = flipY ? -1.0 : 1.0;

    std::vector<PatternItem> items;
    if (pt1on->getValue())
    {
        item.origin.x = rescale(pt1x->getValue(), leapXMin, leapXMax, laserXMin, laserXMax);
        item.origin.y = rescale(pt1y->getValue(), leapYMin, leapYMax, laserYMin, laserYMax);
        items.push_back(item);
    }
    if (pt2on->getValue())
    {
        item.origin.x = rescale(pt2x->getValue(), leapXMin, leapXMax, laserXMin, laserXMax);
        item.origin.y = rescale(pt2y->getValue(), leapYMin, leapYMax, laserYMin, laserYMax);
        items.push_back(item);
    }
    if (pt3on->getValue())
    {
        item.origin.x = rescale(pt3x->getValue(), leapXMin, leapXMax, laserXMin, laserXMax);
        item.origin.y = rescale(pt3y->getValue(), leapYMin, leapYMax, laserYMin, laserYMax);
        items.push_back(item);
    }
    if (pt4on->getValue())
    {
        item.origin.x = rescale(pt4x->getValue(), leapXMin, leapXMax, laserXMin, laserXMax);
        item.origin.y = rescale(pt4y->getValue(), leapYMin, leapYMax, laserYMin, laserYMax);
        items.push_back(item);
    }
    if (pt5on->getValue())
    {
        item.origin.x = rescale(pt5x->getValue(), leapXMin, leapXMax, laserXMin, laserXMax);
        item.origin.y = rescale(pt5y->getValue(), leapYMin, leapYMax, laserYMin, laserYMax);
        items.push_back(item);
    }
    return items;
}

std::vector<PatternItem> chuGenSpirograph::getPatterns(float barClock)
{
    std::vector<PatternItem> items;
    return items;
}