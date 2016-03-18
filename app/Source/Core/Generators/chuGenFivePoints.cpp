/*
  ==============================================================================

    chuGenFivePoints.cpp
    Created: 16 Jan 2016 1:52:58am
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "chuGenFivePoints.h"


chuGenFivePoints::chuGenFivePoints(ValueTree source)
: chuGenerator("FivePoints", source)
{
    addParameter(sides = new chuParameterInt("Sides", 3, 8, 3));
    addParameter(radius = new chuParameterFloat("Radius", 0.01, 0.1, 0.08));
    addParameter(color = new chuParameterColor("Color", Colors::red));

    chuParameterOptions options;
    options.isUserVisible = true;

    addParameter(pt1x  = new chuParameterFloat("pt1x",  leapXMin, leapXMax, (leapXMax - leapXMin)*1.0/6.0 + leapXMin, options));
    addParameter(pt1y  = new chuParameterFloat("pt1y",  leapYMin, leapYMax, (leapYMax + leapYMin)/2.0, options));
    addParameter(pt1on = new chuParameterInt("pt1on", 0, 1, 1, options));
    addParameter(pt2x  = new chuParameterFloat("pt2x",  leapXMin, leapXMax, (leapXMax - leapXMin)*2.0/6.0 + leapXMin, options));
    addParameter(pt2y  = new chuParameterFloat("pt2y",  leapYMin, leapYMax, (leapYMax + leapYMin)/2.0, options));
    addParameter(pt2on = new chuParameterInt("pt2on", 0, 1, 1, options));
    addParameter(pt3x  = new chuParameterFloat("pt3x",  leapXMin, leapXMax, (leapXMax - leapXMin)*3.0/6.0 + leapXMin, options));
    addParameter(pt3y  = new chuParameterFloat("pt3y",  leapYMin, leapYMax, (leapYMax + leapYMin)/2.0, options));
    addParameter(pt3on = new chuParameterInt("pt3on", 0, 1, 1, options));
    addParameter(pt4x  = new chuParameterFloat("pt4x",  leapXMin, leapXMax, (leapXMax - leapXMin)*4.0/6.0 + leapXMin, options));
    addParameter(pt4y  = new chuParameterFloat("pt4y",  leapYMin, leapYMax, (leapYMax + leapYMin)/2.0, options));
    addParameter(pt4on = new chuParameterInt("pt4on", 0, 1, 1, options));
    addParameter(pt5x  = new chuParameterFloat("pt5x",  leapXMin, leapXMax, (leapXMax - leapXMin)*5.0/6.0 + leapXMin, options));
    addParameter(pt5y  = new chuParameterFloat("pt5y",  leapYMin, leapYMax, (leapYMax + leapYMin)/2.0, options));
    addParameter(pt5on = new chuParameterInt("pt5on", 0, 1, 1, options));
}

inline float rescale(float value, float inputMin, float inputMax, float outputMin, float outputMax)
{
    float s = (value - inputMin) / (inputMax - inputMin);
    return outputMin + s * (outputMax - outputMin);
}

void chuGenFivePoints::getPatterns(float barClock, std::vector<PatternItem>& patterns)
{
    PatternItem item;
    item.type = PatternType::RegularPolygon;
    item.sides = sides->getValue();
    item.radius = radius->getValue();
    item.rotation = barClock * 360;
    item.colour = color->getValue();

    bool flipX = false;
    float laserXMin = flipX ? 1.0 : -1.0;
    float laserXMax = flipX ? -1.0 : 1.0;
    bool flipY = false;
    float laserYMin = flipY ? 1.0 : -1.0;
    float laserYMax = flipY ? -1.0 : 1.0;

    if (pt1on->getValue())
    {
        item.origin.x = rescale(pt1x->getValue(), leapXMin, leapXMax, laserXMin, laserXMax);
        item.origin.y = rescale(pt1y->getValue(), leapYMin, leapYMax, laserYMin, laserYMax);
        patterns.push_back(item);
    }
    if (pt2on->getValue())
    {
        item.origin.x = rescale(pt2x->getValue(), leapXMin, leapXMax, laserXMin, laserXMax);
        item.origin.y = rescale(pt2y->getValue(), leapYMin, leapYMax, laserYMin, laserYMax);
        patterns.push_back(item);
    }
    if (pt3on->getValue())
    {
        item.origin.x = rescale(pt3x->getValue(), leapXMin, leapXMax, laserXMin, laserXMax);
        item.origin.y = rescale(pt3y->getValue(), leapYMin, leapYMax, laserYMin, laserYMax);
        patterns.push_back(item);
    }
    if (pt4on->getValue())
    {
        item.origin.x = rescale(pt4x->getValue(), leapXMin, leapXMax, laserXMin, laserXMax);
        item.origin.y = rescale(pt4y->getValue(), leapYMin, leapYMax, laserYMin, laserYMax);
        patterns.push_back(item);
    }
    if (pt5on->getValue())
    {
        item.origin.x = rescale(pt5x->getValue(), leapXMin, leapXMax, laserXMin, laserXMax);
        item.origin.y = rescale(pt5y->getValue(), leapYMin, leapYMax, laserYMin, laserYMax);
        patterns.push_back(item);
    }
}
