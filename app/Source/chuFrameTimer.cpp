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
        if (logging) {
            printf("Ticked timer at time %f\n", Time::getMillisecondCounterHiRes());
        }
        
        auto& patterns = laserThread->getOutputBuffer().getPatternQueue();

        patterns.start_frame();
        for (auto& generator : getGeneratorManager()->getAllGenerators())
        {
            if (generator->isActive())
            {
                auto items = generator->getPatterns(barClock);
                for (auto& item : items)
                {
                    patterns.push_item(item);
                }
            }
        }
        patterns.finish_frame();
    }
}

void chuFrameTimer::syncBeatClock()
{
    numPulses = 0;
    setBarClock(0);
    isRunning = true;
}

void chuFrameTimer::handleIncomingMidiMessage(MidiInput*, const MidiMessage& message)
{
    if (message.isMidiClock() && isRunning)
    {
        numPulses++;
        if (numPulses > pulsesPerBar) {
            numPulses -= pulsesPerBar;
        }

        setBarClock(numPulses / (pulsesPerBar * 1.0));
    }
    else if (message.isMidiStart())
    {
        numPulses = 0;
        isRunning = true;
    }
    else if (message.isMidiStop())
    {
        isRunning = false;
    }
}