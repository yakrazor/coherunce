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

class chuFrameTimer : public Timer
{
public:
    chuFrameTimer(LaserOutputThread* pLaserThread) : laserThread(pLaserThread) {}
    void timerCallback() override;
private:
    LaserOutputThread* laserThread;
};



#endif  // CHUFRAMETIMER_H_INCLUDED
