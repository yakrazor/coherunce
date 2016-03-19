/*
  ==============================================================================

    chuGenNoiseEffect.cpp
    Created: 18 Mar 2016 6:04:12pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "chuGenNoiseEffect.h"

#include <random>

// set up random distribution;
std::mt19937 engine;
std::normal_distribution<float> dist(-0.1, 0.1);

chuGenNoiseEffect::chuGenNoiseEffect(ValueTree source)
: chuGenerator("NoiseEffect", source)
{
    addParameter(amount = new chuParameterFloat("Amount", 0.0, 1.0, 0.0));
}

void chuGenNoiseEffect::getPatterns(float barClock, std::vector<PatternItem>& patterns)
{
    if (fabs(amount->getValue()) < 0.00001)
    {
        return;
    }

    for (auto& item : patterns)
    {
        item.convertToPolyline();
        if (item.type == PatternType::Polyline)
        {
            // move the start and endpoint by the same amount, to not break closed shapes
            float startX = dist(engine) * amount->getValue();
            float startY = dist(engine) * amount->getValue();
            item.polyline.vertices[0].x += startX;
            item.polyline.vertices[0].y += startY;
            item.polyline.vertices[item.polyline.vertices.size() - 1].x += startX;
            item.polyline.vertices[item.polyline.vertices.size() - 1].y += startY;

            for (int i = 1; i < item.polyline.vertices.size() - 1; i++)
            {
                item.polyline.vertices[i].x += dist(engine) * amount->getValue();
                item.polyline.vertices[i].y += dist(engine) * amount->getValue();
            }
        }
    }

}