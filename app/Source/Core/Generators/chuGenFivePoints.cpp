/*
  ==============================================================================

    chuGenFivePoints.cpp
    Created: 16 Jan 2016 1:52:58am
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "chuGenFivePoints.h"


chuGenFivePoints::chuGenFivePoints()
: chuGenerator("FivePoints")
{
    sides = new chuParameterInt("Sides", 3, 8, 3);
    radius = new chuParameterFloat("Radius", 0.01, 0.1, 0.08);

    color = new chuParameterColor("Color", Colors::red);

    chuParameterOptions options;
    options.isUserVisible = true;

    pt1x  = new chuParameterFloat("pt1x",  leapXMin, leapXMax, (leapXMax - leapXMin)*1.0/6.0 + leapXMin, options);
    pt1y  = new chuParameterFloat("pt1y",  leapYMin, leapYMax, (leapYMax + leapYMin)/2.0, options);
    pt1on = new chuParameterInt("pt1on", 0, 1, 1, options);
    pt2x  = new chuParameterFloat("pt2x",  leapXMin, leapXMax, (leapXMax - leapXMin)*2.0/6.0 + leapXMin, options);
    pt2y  = new chuParameterFloat("pt2y",  leapYMin, leapYMax, (leapYMax + leapYMin)/2.0, options);
    pt2on = new chuParameterInt("pt2on", 0, 1, 1, options);
    pt3x  = new chuParameterFloat("pt3x",  leapXMin, leapXMax, (leapXMax - leapXMin)*3.0/6.0 + leapXMin, options);
    pt3y  = new chuParameterFloat("pt3y",  leapYMin, leapYMax, (leapYMax + leapYMin)/2.0, options);
    pt3on = new chuParameterInt("pt3on", 0, 1, 1, options);
    pt4x  = new chuParameterFloat("pt4x",  leapXMin, leapXMax, (leapXMax - leapXMin)*4.0/6.0 + leapXMin, options);
    pt4y  = new chuParameterFloat("pt4y",  leapYMin, leapYMax, (leapYMax + leapYMin)/2.0, options);
    pt4on = new chuParameterInt("pt4on", 0, 1, 1, options);
    pt5x  = new chuParameterFloat("pt5x",  leapXMin, leapXMax, (leapXMax - leapXMin)*5.0/6.0 + leapXMin, options);
    pt5y  = new chuParameterFloat("pt5y",  leapYMin, leapYMax, (leapYMax + leapYMin)/2.0, options);
    pt5on = new chuParameterInt("pt5on", 0, 1, 1, options);
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
