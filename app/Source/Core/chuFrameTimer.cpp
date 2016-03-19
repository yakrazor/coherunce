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

chuFrameTimer::chuFrameTimer(LaserOutputThread* pLaserThread) : laserThread(pLaserThread), numPulses(0), barClock(0)
{
    bars = 0;
    bpmValue.setValue(120.0);
    isClockExternalValue.setValue(false);
    beatDeltaMillisecondsValue.setValue(24.0);
    isClockRunningValue.setValue(true);
    quantizedBeatClockValue.setValue(0);
}

void chuFrameTimer::setBarClock(float clock)
{
    if (clock < 0 || clock > 1) {
        printf("Bad clock value");
        return;
    }
    barClock = clock;
    numPulses = pulsesPerBar * barClock;

    int quantClock = ceil(barClock * 4.0);
    int currentQuantClockVal = quantizedBeatClockValue.getValue();
    if (currentQuantClockVal != quantClock) {
        quantizedBeatClockValue.setValue(quantClock);
    }
}

void chuFrameTimer::setExternalClock(bool isExternal)
{
    if (isClockExternal() && isExternal == false)
    {
        // set timer to match current bar position, to switch from external to internal without jumping
        double timeStamp = Time::getMillisecondCounterHiRes();
        lastDownbeatTimestamp = timeStamp - ((float)beatDeltaMillisecondsValue.getValue() * barClock * quarterNotesPerBar);
    }

    isClockExternalValue.setValue(isExternal);
}

void chuFrameTimer::setRunning(bool isRunning)
{
    if (!isClockRunning() && isRunning == true)
    {
        // set timer to match current bar position, to restart without jumping
        double timeStamp = Time::getMillisecondCounterHiRes();
        lastDownbeatTimestamp = timeStamp - ((float)beatDeltaMillisecondsValue.getValue() * barClock * quarterNotesPerBar);
    }

    isClockRunningValue.setValue(isRunning);
}

void chuFrameTimer::timerCallback()
{
    if (logging) {
        printf("Ticked timer at time %f\n", Time::getMillisecondCounterHiRes());
    }

    if (!isClockExternal() && isClockRunning())
    {
        double timeStamp = Time::getMillisecondCounterHiRes();
        double deltaMs = beatDeltaMillisecondsValue.getValue();

        if ((timeStamp - lastDownbeatTimestamp) > (deltaMs * quarterNotesPerBar))
        {
            bars = (bars + 1) % 64;
            lastDownbeatTimestamp = Time::getMillisecondCounterHiRes();
            timeStamp = Time::getMillisecondCounterHiRes();
        }

        setBarClock((timeStamp - lastDownbeatTimestamp) / (deltaMs * quarterNotesPerBar));
    }

    if (laserThread) {

        std::vector<PatternItem> patterns;

        for (auto& generator : getGeneratorManager()->getAllGenerators())
        {
            if (generator->isActive())
            {
                generator->getPatterns(getBarClock64(), patterns);
            }
        }

        for (auto& generator : getGeneratorManager()->getGlobalEffects())
        {
            if (generator->isActive())
            {
                generator->getPatterns(getBarClock64(), patterns);
            }
        }

        auto& queue = laserThread->getOutputBuffer().getPatternQueue();
        queue.start_frame();
        queue.push_items(patterns);
        queue.finish_frame();
    }
}

void chuFrameTimer::syncBeatClock()
{
    setBarClock(0);
    setRunning(true);
    lastDownbeatTimestamp = Time::getMillisecondCounterHiRes();
}

void chuFrameTimer::tapTempo()
{
    if (isClockExternal()) {
        // We can't modify external clock timing, only internal
        return;
    }
    double tapTimestamp = Time::getMillisecondCounterHiRes();
    double deltaMs = tapTimestamp - lastTapTempoTimestamp;
    lastTapTempoTimestamp = tapTimestamp;
    if (deltaMs > tapTempoMaxDeltaMs) {
        return;
    }
    bpmValue.setValue(beatMsNumerator / deltaMs);
    beatDeltaMillisecondsValue.setValue(deltaMs);
}

void chuFrameTimer::setBpm(double newBpm)
{
    if (isClockExternal()) {
        // We can't modify external clock timing, only internal
        return;
    }
    setBpmRaw(newBpm);
}

void chuFrameTimer::setBpmRaw(double newBpm)
{
    bpmValue.setValue(newBpm);
    beatDeltaMillisecondsValue.setValue(beatMsNumerator / newBpm);
}


void chuFrameTimer::handleIncomingMidiMessage(MidiInput*, const MidiMessage& message)
{
    double pulseDelta = 0.0;
    double currentPulseTimestamp = 0.0;

    if (message.isMidiClock())
    {
        // Update bar clock only if clock is running
        if (isClockRunning() && isClockExternal())
        {
            numPulses++;
            if (numPulses > pulsesPerBar) {
                bars = (bars + 1) % 64;
                numPulses -= pulsesPerBar;
            }

            setBarClock(numPulses / (pulsesPerBar * 1.0));
        }

        // Track external clock even when clock is internal or not running, for correct BPM display
        currentPulseTimestamp = Time::getMillisecondCounterHiRes();
        pulseDelta = currentPulseTimestamp - lastMidiClockTimestamp;
        int numPulsesToKeep = pulsesPerQuarterNote * externalClockAveragingWindowMilliseconds / (float)beatDeltaMillisecondsValue.getValue();
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
            beatDeltaMillisecondsValue.setValue((clockPulseDeltaAccumulator / midiClockPulseDeltas.size()) * pulsesPerQuarterNote);
        } else {
            beatDeltaMillisecondsValue.setValue(pulseDelta * pulsesPerQuarterNote);
        }
        double new_bpm = beatMsNumerator / getMsBetweenBeats();
        double old_bpm = bpmExternal;
        if (fabs(old_bpm - new_bpm) > bpmDeltaSmoothing) {
            bpmExternal = new_bpm;
        }
        if (isClockExternal())
        {
            setBpmRaw(bpmExternal);
        }
    }
    else if (message.isMidiStart() && isClockExternal())
    {
        setBarClock(0);
        setRunning(true);
    }
    else if (message.isMidiStop() && isClockExternal())
    {
        setRunning(false);
    }
}