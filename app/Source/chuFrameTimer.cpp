/*
  ==============================================================================

    chuFrameTimer.cpp
    Created: 29 Dec 2015 5:21:21pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "chuFrameTimer.h"
#include "LaserOutputThread.h"
#include "chuGenerator.h"

void chuFrameTimer::timerCallback() {
    if (laserThread) {
        printf("Ticked timer at time %f\n", Time::getMillisecondCounterHiRes());

        OwnedArray<chuGenerator> allGenerators;
        auto pinwheel = new chuGenPolygonPinwheel();
        pinwheel->setActive(true);
        allGenerators.add(pinwheel);

        laserThread->patterns.start_frame();

        for (auto& generator : allGenerators)
        {
            if (generator->isActive())
            {
                auto items = generator->getPatterns();
                for (auto& item : items)
                {
                    laserThread->patterns.push_item(item);
                }
            }
        }

        laserThread->patterns.finish_frame();
    }
}