/*
  ==============================================================================

    LaserOutputThread.h
    Created: 24 Dec 2015 12:04:33am
    Author:  Michael Dewberry

  ==============================================================================
*/

#ifndef LASEROUTPUTTHREAD_H_INCLUDED
#define LASEROUTPUTTHREAD_H_INCLUDED


#include "../JuceLibraryCode/JuceHeader.h"
#include "chuThreadQueue.h"
#include "PatternItem.h"


class LaserOutputThread : public Thread
{
public:
    LaserOutputThread();
    ~LaserOutputThread();
    bool init();
    void run() override;

    chuThreadQueue<PatternItem> patterns;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LaserOutputThread)
    bool connected;
};


#endif  // LASEROUTPUTTHREAD_H_INCLUDED
