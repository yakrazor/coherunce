/*
  ==============================================================================

    PatternItem.cpp
    Created: 18 Mar 2016 6:09:11pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "PatternItem.h"

#define PI 3.1415926

void PatternItem::convertToPolyline()
{
    if (type == PatternType::RegularPolygon)
    {
        type = PatternType::Polyline;

        // Find the start point
        float rad = rotation * PI/180.0;
        float x = (origin.x + radius * cos(rad));
        float y = (origin.y + radius * sin(rad));
        polyline.addPoint(Vector2f(x, y), colour);

        for (int i = 1; i < sides + 1; i++) {
            x = (origin.x + radius * cos(2 * PI * i / sides + rad));
            y = (origin.y + radius * sin(2 * PI * i / sides + rad));
            polyline.addPoint(Vector2f(x, y), colour);
        }
    }
}