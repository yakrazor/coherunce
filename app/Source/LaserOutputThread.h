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
#include "chuParameter.h"

extern bool logging;

class LaserConfig : public chuParameterProvider
{
public:
    LaserConfig();

    const int ildaXMin = -32768;
    const int ildaXMax = 32767;
    const int ildaYMin = -32768;
    const int ildaYMax = 32767;
    const int ildaIntensityMin = 0;
    const int ildaIntensityMax = 65535;

    chuParameterInt pointsPerSecond;
    chuParameterInt longestUnbrokenLine;
    chuParameterInt internalDwellPoints;
    chuParameterInt dwellOffPoints;
    chuParameterInt dwellOnPoints;

    virtual void getParamList(std::vector<chuParameter*>& params) override;
    virtual String getName() const override { return "Laser Config"; }
};

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

    LaserConfig& getLaserConfig() { return laserConfig; }

    void setGlobalIntensity(float intensity) { globalIntensity = intensity; }

    chuThreadQueue<PatternItem> patterns;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LaserOutputThread)
    bool connected;

    float globalIntensity;
    bool enabled;

    LaserConfig laserConfig;
};


#endif  // LASEROUTPUTTHREAD_H_INCLUDED
