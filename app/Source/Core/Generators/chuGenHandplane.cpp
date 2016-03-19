/*
  ==============================================================================

    chuGenHandplane.cpp
    Created: 18 Mar 2016 9:33:03pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "chuGenHandplane.h"

chuGenHandplane::chuGenHandplane(ValueTree source)
: chuGenerator("Handplane", source)
{
    addParameter(color1 = new chuParameterColor("Color1", Colors::blue));
    addParameter(color2 = new chuParameterColor("Color2", Colors::green));
    addParameter(extend = new chuParameterBool("Extend", false));

    chuParameterOptions options;
    options.isUserVisible = true;

    addParameter(pt2x  = new chuParameterFloat("pt2x",  leapXMin, leapXMax, (leapXMax - leapXMin)*1.0/6.0 + leapXMin, options));
    addParameter(pt2y  = new chuParameterFloat("pt2y",  leapYMin, leapYMax, (leapYMax + leapYMin)/2.0, options));
    addParameter(pt3x  = new chuParameterFloat("pt3x",  leapXMin, leapXMax, (leapXMax - leapXMin)*2.0/6.0 + leapXMin, options));
    addParameter(pt3y  = new chuParameterFloat("pt3y",  leapYMin, leapYMax, (leapYMax + leapYMin)/2.0, options));
}

inline float rescale(float value, float inputMin, float inputMax, float outputMin, float outputMax)
{
    float s = (value - inputMin) / (inputMax - inputMin);
    return outputMin + s * (outputMax - outputMin);
}

void chuGenHandplane::getPatterns(float barClock, std::vector<PatternItem>& patterns)
{
    PatternItem item;
    item.type = PatternType::Polyline;

    bool flipX = false;
    float laserXMin = flipX ? 1.0 : -1.0;
    float laserXMax = flipX ? -1.0 : 1.0;
    bool flipY = false;
    float laserYMin = flipY ? 1.0 : -1.0;
    float laserYMax = flipY ? -1.0 : 1.0;

    float x1 = rescale(pt2x->getValue(), leapXMin, leapXMax, laserXMin, laserXMax);
    float y1 = rescale(pt2y->getValue(), leapYMin, leapYMax, laserYMin, laserYMax);

    float x2 = rescale(pt3x->getValue(), leapXMin, leapXMax, laserXMin, laserXMax);
    float y2 = rescale(pt3y->getValue(), leapYMin, leapYMax, laserYMin, laserYMax);

    Vector2f start(x1, y1);
    Vector2f end(x2, y2);

    if (extend->getValue())
    {
        Vector2f d = (end - start).normalized();
        float sx = ((start.x < end.x ? -1 : 1) - start.x) / d.x;
        float sy = ((start.y < end.y ? -1 : 1) - start.y) / d.y;
        float ex = ((end.x <= start.x ? -1 : 1) - end.x) / d.x;
        float ey = ((end.y <= start.y ? -1 : 1) - end.y) / d.y;

        start = (fabs(sx) < fabs(sy)) ? start + d * sx : start + d * sy;
        end = (fabs(ex) < fabs(ey)) ? end + d * ex : end + d * ey;
    }

    item.polyline.vertices.push_back(start);
    item.polyline.vertices.push_back(end);
    item.polyline.colours.push_back(color1->getValue());
    item.polyline.colours.push_back(color2->getValue());

    patterns.push_back(item);
}
