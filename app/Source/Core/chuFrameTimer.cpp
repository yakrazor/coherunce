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

chuFrameTimer::chuFrameTimer(LaserOutputThread* pLaserThread) : laserThread(pLaserThread), numPulses(0)
{
    bpm = new bpmValue();
    external = new externalClockValue();
    delta = new beatDeltaMsValue();
    running = new clockRunningValue();
    
    bpm->setValue(120.0);
    external->setValue(true);
    delta->setValue(24.0);
    running->setValue(true);
}

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
    running->setValue(true);
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
    
    if (message.isMidiClock() && isClockRunning())
    {
        numPulses++;
        if (numPulses > pulsesPerBar) {
            numPulses -= pulsesPerBar;
        }
        if (isClockExternal()) {

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
                delta->setValue(clockPulseDeltaAccumulator / midiClockPulseDeltas.size());
            } else {
                delta->setValue(pulseDelta);
            }
            double new_bpm = msNumerator / getMsBetweenBeats();
            double old_bpm = getBpm();
            if (fabs(old_bpm - new_bpm) > bpmDeltaSmoothing) {
                bpm->setValue(new_bpm);
            }
            setBarClock(numPulses / (pulsesPerBar * 1.0));
        }
    }
    else if (message.isMidiStart())
    {
        numPulses = 0;
        running->setValue(true);
        printf("Midi clock start\n");
    }
    else if (message.isMidiStop())
    {
        running->setValue(false);
        printf("Midi clock stop\n");
    }
}