/*
  ==============================================================================

    patterns.h
    Created: 30 Dec 2015 1:36:56pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#ifndef PATTERNS_H_INCLUDED
#define PATTERNS_H_INCLUDED


struct Vector2f
{
    Vector2f() : x(0), y(0) {}
    Vector2f(float _x, float _y) : x(_x), y(_y) {}
    float x;
    float y;
};

typedef enum {
    Point = 0,
    Line,
    Polyline,
    Rectangle,
    Ellipse,
    RegularPolygon
} PatternType;

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
    std::vector<Vector2f> points;
};


#endif  // PATTERNS_H_INCLUDED
