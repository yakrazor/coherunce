/*
  ==============================================================================

    chuFrameTimer.cpp
    Created: 29 Dec 2015 5:21:21pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "chuFrameTimer.h"
#include "LaserOutputThread.h"

void chuFrameTimer::timerCallback() {
    if (laserThread) {
        printf("Ticked timer at time %f\n", Time::getMillisecondCounterHiRes());

        PatternItem item;
        item.type = PatternType::RegularPolygon;
        item.sides = 5;
        item.radius = 1.00;
        item.origin = Vector2f(0, 0);
        item.rotation = Time::getMillisecondCounterHiRes() * 180/1200.0;

        laserThread->patterns.start_frame();
        laserThread->patterns.push_item(item);
        item.radius *= 0.66;
        item.rotation *= -1;
        laserThread->patterns.push_item(item);
        item.radius *= 0.66;
        item.rotation *= -1;
        laserThread->patterns.push_item(item);
        laserThread->patterns.finish_frame();
    }
}