/*
  ==============================================================================

    chuGenSinusoidEffect.cpp
    Created: 18 Mar 2016 6:03:54pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "chuGenSinusoidEffect.h"

#define PI 3.1415926

chuGenSinusoidEffect::chuGenSinusoidEffect(ValueTree source)
: chuGenerator("SinusoidEffect", source)
{
    addParameter(amount = new chuParameterFloat("Amount", 0.0, 1.0, 0.0));
    addParameter(samples = new chuParameterInt("Samples", 3, 12, 6));
}

void chuGenSinusoidEffect::getPatterns(float barClock, std::vector<PatternItem>& patterns)
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
            Polyline2f newLine;
            for (int i = 0; i < item.polyline.vertices.size() - 1; i++)
            {
                Vector2f start = item.polyline.vertices[i];
                Vector2f end = item.polyline.vertices[i + 1];
                Vector2f forwardVec = (end - start).normalized();
                Vector2f normalVec = Vector2f(forwardVec.y, forwardVec.x);

                float length = (end - start).length();
                float delta = length / (1.0 * samples->getValue());

                Color startColor = item.polyline.colours[i];
                Color endColor = item.polyline.colours[i + 1];

                Vector2f pt = start;
                newLine.vertices.push_back(start);
                newLine.colours.push_back(startColor);
                for (int k = 1; k < samples->getValue() - 1; k++)
                {
                    float s = k / (1.0 * samples->getValue());
                    pt = pt + (forwardVec * delta);
                    newLine.vertices.push_back(pt + amount->getValue() * 0.1 * (normalVec * sin(s * 2 * PI)));
                    newLine.colours.push_back(startColor.interpolatedWith(endColor, s));
                }
                newLine.vertices.push_back(end);
                newLine.colours.push_back(endColor);

            }
            item.polyline = newLine;
        }
    }

}