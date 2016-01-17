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

class chuFrameTimer : public Timer, public MidiInputCallback
{
public:
    chuFrameTimer(LaserOutputThread* pLaserThread) : laserThread(pLaserThread), numPulses(0), externalClock(false) {}
    void timerCallback() override;

    void setBarClock(float clock) { barClock = clock; }
    float getBarClock() { return barClock; }
    void setExternalClock(bool useExternalClock);
    void syncBeatClock();

    void handleIncomingMidiMessage (MidiInput*, const MidiMessage& message) override;

private:
    LaserOutputThread* laserThread;
    float barClock;
    bool isRunning;

    unsigned int numPulses;
    bool externalClock;
    const unsigned int pulsesPerQuarterNote = 24;
    const unsigned int quarterNotesPerBar = 4;
    const unsigned int pulsesPerBar = pulsesPerQuarterNote * quarterNotesPerBar;
};


#endif  // CHUFRAMETIMER_H_INCLUDED
