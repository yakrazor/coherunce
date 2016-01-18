/*
  ==============================================================================

    patterns.h
    Created: 30 Dec 2015 1:36:56pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#ifndef PATTERNS_H_INCLUDED
#define PATTERNS_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

struct Vector2f
{
    Vector2f() : x(0), y(0) {}
    Vector2f(float _x, float _y) : x(_x), y(_y) {}
    float x;
    float y;
};

class Polyline2f
{
public:
    Polyline2f()
    {
    }
    
    void addPoint(const Vector2f& point, const Colour& colour)
    {
        vertices.push_back(point);
        colours.push_back(colour);
    }

    size_t size() { return vertices.size(); }

    std::vector<Vector2f> vertices;
    std::vector<Colour> colours;
};

enum PatternType {
    Point = 0,
    Line,
    Polyline,
    Rectangle,
    Ellipse,
    RegularPolygon
};

struct PatternItem
{
    PatternItem()
    : type(PatternType::Point), origin(0,0), rotation(0), red(65535), green(0), blue(0), width(0), radius(0), height(0), sides(0) {}

    PatternType type;
    Vector2f origin;
    float rotation;
    uint16_t red;
    uint16_t green;
    uint16_t blue;

    float width;
    float radius;
    float height;
    int sides;
    Polyline2f polyline;
};


#endif  // PATTERNS_H_INCLUDED
