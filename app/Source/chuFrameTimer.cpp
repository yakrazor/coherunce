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
#include "chuGeneratorManager.h"

void chuFrameTimer::timerCallback() {
    if (laserThread) {
        printf("Ticked timer at time %f\n", Time::getMillisecondCounterHiRes());

        laserThread->patterns.start_frame();

        for (auto& generator : chuGeneratorManager::getAllGenerators())
        {
            if (generator->isActive())
            {
                auto items = generator->getPatterns(barClock);
                for (auto& item : items)
                {
                    laserThread->patterns.push_item(item);
                }
            }
        }

        laserThread->patterns.finish_frame();
    }
}

void chuFrameTimer::handleIncomingMidiMessage(MidiInput*, const MidiMessage& message)
{
    if (message.isMidiClock())
    {
        numPulses++;
        if (numPulses > pulsesPerBar) {
            numPulses -= pulsesPerBar;
        }

        setBarClock(numPulses / (pulsesPerBar * 1.0));
    }
}