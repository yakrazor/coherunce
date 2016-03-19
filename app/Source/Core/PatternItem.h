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

    inline float length() const { return sqrtf(x * x + y * y); }
    inline Vector2f normalized() const { float l = length(); return Vector2f(x / l, y / l); }

};

inline Vector2f operator+(const Vector2f& a, const Vector2f& b)
{
    return Vector2f(a.x + b.x, a.y + b.y);
}

inline Vector2f operator-(const Vector2f& a, const Vector2f& b)
{
    return Vector2f(a.x - b.x, a.y - b.y);
}

inline Vector2f operator*(const Vector2f& a, float s)
{
    return Vector2f(a.x * s, a.y * s);
}

inline Vector2f operator*(float s, const Vector2f& a)
{
    return Vector2f(a.x * s, a.y * s);
}


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
    : type(PatternType::Point), origin(0,0), rotation(0), colour(Colours::red), width(0), radius(0), height(0), sides(0) {}

    PatternType type;
    Vector2f origin;
    float rotation;
    Colour colour;

    float width;
    float radius;
    float height;
    int sides;
    Polyline2f polyline;

    void convertToPolyline();
};


#endif  // PATTERNS_H_INCLUDED
