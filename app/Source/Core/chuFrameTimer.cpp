/*
  ==============================================================================

    chuFrameTimer.cpp
    Created: 29 Dec 2015 5:21:21pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "chuFrameTimer.h"
#include "LaserOutputThread.h"
#include "Generators/chuGenerator.h"
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

void chuFrameTimer::tapTempo() {
    // Handle tap tempo event
}

void chuFrameTimer::setExternalClock(bool external)
{
    // Toggle between internal and external clock source
}

void chuFrameTimer::handleIncomingMidiMessage(MidiInput*, const MidiMessage& message)
{
    double pulseDelta = 0.0;
    double currentPulseTimestamp = 0.0;
    
    if (message.isMidiClock() && isRunning)
    {
        numPulses++;
        if (numPulses > pulsesPerBar) {
            numPulses -= pulsesPerBar;
        }
        if (externalClock) {

            currentPulseTimestamp = Time::getMillisecondCounterHiRes();
            pulseDelta = currentPulseTimestamp - lastMidiClockTimestamp;
            lastMidiClockTimestamp = currentPulseTimestamp;
            midiClockPulseDeltas.insert(0, pulseDelta);
            if (midiClockPulseDeltas.size() > numPulsesToKeep) {
                midiClockPulseDeltas.resize(numPulsesToKeep);
            }
            if (midiClockPulseDeltas.size() > 0) {
                double clockPulseDeltaAccumulator = 0;
                for(int idx = 0; idx < midiClockPulseDeltas.size(); idx++) {
                    clockPulseDeltaAccumulator += midiClockPulseDeltas[idx];
                }
                barClockMsDelta = clockPulseDeltaAccumulator / midiClockPulseDeltas.size();
            } else {
                barClockMsDelta = pulseDelta;
            }
            double bpm = msNumerator / barClockMsDelta;
            double old_bpm = getValue();
            if (fabs(old_bpm - bpm) > bpmDeltaSmoothing) {
                setValue(bpm);
            }
            setBarClock(numPulses / (pulsesPerBar * 1.0));
        }
    }
    else if (message.isMidiStart())
    {
        numPulses = 0;
        isRunning = true;
        printf("Midi clock start\n");
    }
    else if (message.isMidiStop())
    {
        isRunning = false;
        printf("Midi clock stop\n");
    }
}