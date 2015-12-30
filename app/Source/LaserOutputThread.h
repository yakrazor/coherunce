/*
  ==============================================================================

    LaserOutputThread.h
    Created: 24 Dec 2015 12:04:33am
    Author:  Michael Dewberry

  ==============================================================================
*/

#ifndef LASEROUTPUTTHREAD_H_INCLUDED
#define LASEROUTPUTTHREAD_H_INCLUDED


#include "../JuceLibraryCode/JuceHeader.h"
#include "chuThreadQueue.h"

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
        : type(PatternType::Point), origin(0,0), rotation(0), red(65536), green(65536), blue(65536), width(0), radius(0), height(0), sides(0) {}

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
    Vector2f points[12];
};

class LaserOutputThread : public Thread
{
public:
    LaserOutputThread();
    ~LaserOutputThread();
    bool init();
    void run() override;

    chuThreadQueue<PatternItem> patterns;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LaserOutputThread)
    bool connected;
};


#endif  // LASEROUTPUTTHREAD_H_INCLUDED
