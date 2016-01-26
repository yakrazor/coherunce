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
    chuFrameTimer(LaserOutputThread* pLaserThread);
    void timerCallback() override;

    void setBarClock(float clock);
    float getBarClock() { return barClock; };

    void setExternalClock(bool isExternal);
    void setRunning(bool isRunning);
    void syncBeatClock();
    void tapTempo();
    
    double getBpm() { return bpmValue.getValue(); }
    double getMsBetweenBeats() { return beatDeltaMillisecondsValue.getValue(); }
    void setBpm(double newBpm);
    
    bool isClockExternal() { return isClockExternalValue.getValue(); }
    bool isClockRunning() { return isClockRunningValue.getValue(); }
    
    Value bpmValue;
    Value isClockExternalValue;
    Value beatDeltaMillisecondsValue;
    Value isClockRunningValue;
    Value quantizedBeatClockValue;
    
    void handleIncomingMidiMessage (MidiInput*, const MidiMessage& message) override;

private:
    LaserOutputThread* laserThread;
    float barClock;
    unsigned int numPulses;
    double lastMidiClockTimestamp;
    double lastDownbeatTimestamp;
    double lastTapTempoTimestamp;
    Array<double> midiClockPulseDeltas;

    float bpmExternal;
    void setBpmRaw(double newBpm);
    
    const unsigned int pulsesPerQuarterNote = 24;
    const unsigned int quarterNotesPerBar = 4;
    const unsigned int pulsesPerBar = pulsesPerQuarterNote * quarterNotesPerBar;
    const unsigned int beatMsNumerator = 60000;
    const unsigned int externalClockAveragingWindowMilliseconds = 600;
    const unsigned int tapTempoMaxDeltaMs = 5000;
    const float bpmDeltaSmoothing = 0.1;
};


#endif  // CHUFRAMETIMER_H_INCLUDED
