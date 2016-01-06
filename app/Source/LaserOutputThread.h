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
#include "LaserOutputDriver.h"
#include "LaserOutputBuffer.h"
#include "LaserConfig.h"

extern bool logging;

class LaserOutputThread : public Thread
{
public:
    LaserOutputThread();
    ~LaserOutputThread();
    bool init();
    void run() override;

    void enableOutput();
    void disableOutput();
    bool isOutputEnabled();

    int getFPS();
    int getPointCount();

    LaserConfig& getLaserConfig() { return laserConfig; }
    LaserOutputBuffer& getOutputBuffer() { return outputBuffer; }
    const LaserStatistics& getStatistics() const { return stats; }

    void setGlobalIntensity(float intensity) { globalIntensity = intensity; }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LaserOutputThread)

    float globalIntensity;

    LaserStatistics stats;
    LaserConfig laserConfig;
    LaserOutputBuffer outputBuffer;

    ScopedPointer<LaserOutputDriver> outputDriver;
    ScopedPointer<LaserOutputDevice> outputDevice;
};


#endif  // LASEROUTPUTTHREAD_H_INCLUDED
