/*
  ==============================================================================

    chuGen16Step.cpp
    Created: 16 Jan 2016 1:52:05am
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "chuGen16Step.h"

chuGen16Step::chuGen16Step(ValueTree source)
: chuGenerator("16Step", source)
{
    addParameter(height = new chuParameterFloat("Height", 0.01, 1.0, 0.3));
    addParameter(quantized = new chuParameterBool("Quantize", true));
    addParameter(numSteps = new chuParameterInt("Steps", 2, 16, 16));
    
    addParameter(pointiness = new chuParameterFloat("Pointiness", 0.0, 1.0, 0.0));
    addParameter(restColor = new chuParameterColor("RestColor", Colors::blue));
    addParameter(activeColor = new chuParameterColor("ActiveColor", Colors::red));
}

void chuGen16Step::getPatterns(float barClock, std::vector<PatternItem>& patterns)
{
    int count = numSteps->getValue();
    float step = barClock * (count - 1);
    if (quantized->getValue())
    {
        step = floorf(fmodf(barClock * count, count));
    }
    float stepScaled = step/(count * 0.5) - 1.0;
    float barWidth = 2.0 /(count * 1.0);
    float pointShift = barWidth * pointiness->getValue() * 0.5;

    PatternItem item;
    item.type = PatternType::Polyline;
    item.origin = Vector2f(0, 0);

    item.polyline.addPoint(Vector2f(-1, -height->getValue()), restColor->getValue());
    if (step > 0)
    {
        item.polyline.addPoint(Vector2f(stepScaled, -height->getValue()), restColor->getValue());
    }
    item.polyline.addPoint(Vector2f(stepScaled + pointShift, height->getValue()), activeColor->getValue());
    item.polyline.addPoint(Vector2f(stepScaled + barWidth - pointShift, height->getValue()), activeColor->getValue());
    if (step < 15)
    {
        item.polyline.addPoint(Vector2f(stepScaled + barWidth, -height->getValue()), restColor->getValue());
    }
    item.polyline.addPoint(Vector2f(1, -height->getValue()), restColor->getValue());

    patterns.push_back(item);
}