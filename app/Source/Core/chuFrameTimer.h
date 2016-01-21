/*
  ==============================================================================

    chuFrameTimer.h
    Created: 29 Dec 2015 5:13:35pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#ifndef CHUFRAMETIMER_H_INCLUDED
#define CHUFRAMETIMER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class LaserOutputThread;


class bpmValue : public Value {
};

class externalClockValue : public Value {
};

class clockRunningValue : public Value {
};

class beatDeltaMsValue : public Value {
};

class chuFrameTimer : public Timer, public MidiInputCallback
{
public:
    chuFrameTimer(LaserOutputThread* pLaserThread);
    void timerCallback() override;

    void setBarClock(float clock) { barClock = clock; };
    float getBarClock() { return barClock; };

    void setExternalClock(bool isExternal) { external->setValue(isExternal); }
    void setRunning(bool isRunning) { running->setValue(isRunning); }
    void syncBeatClock();
    void tapTempo();
    
    double getBpm() { return bpm->getValue(); }
    double getMsBetweenBeats() { return delta->getValue(); }
    void setBpm(double newBpm);
    
    bool isClockExternal() { return external->getValue(); }
    bool isClockRunning() { return running->getValue(); }
    
    ScopedPointer<bpmValue> bpm;
    ScopedPointer<externalClockValue> external;
    ScopedPointer<beatDeltaMsValue> delta;
    ScopedPointer<clockRunningValue> running;

    
    void handleIncomingMidiMessage (MidiInput*, const MidiMessage& message) override;

private:
    LaserOutputThread* laserThread;
    float barClock;
    unsigned int numPulses;
    double lastMidiClockTimestamp;
    Array<double> midiClockPulseDeltas;
    
    
    const unsigned int pulsesPerQuarterNote = 24;
    const unsigned int quarterNotesPerBar = 4;
    const unsigned int pulsesPerBar = pulsesPerQuarterNote * quarterNotesPerBar;
    const unsigned int msNumerator = 2500;
    const unsigned int numPulsesToKeep = 100;
    const float bpmDeltaSmoothing = 0.1;
};


#endif  // CHUFRAMETIMER_H_INCLUDED
