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

class chuFrameTimer : public Timer, public MidiInputCallback, public Value
{
public:
    chuFrameTimer(LaserOutputThread* pLaserThread) : laserThread(pLaserThread), numPulses(0), barClockMsDelta(20.8333333), externalClock(true), isRunning(true) {}
    void timerCallback() override;

    void setBarClock(float clock) { barClock = clock; };
    float getBarClock() { return barClock; };

    void setExternalClock(bool);
    void syncBeatClock();
    void tapTempo();

    void handleIncomingMidiMessage (MidiInput*, const MidiMessage& message) override;

private:
    LaserOutputThread* laserThread;
    float barClock;
    double barClockMsDelta;
    bool isRunning;

    unsigned int numPulses;
    bool externalClock;
    
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
