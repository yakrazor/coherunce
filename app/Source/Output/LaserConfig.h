/*
  ==============================================================================

    LaserConfig.h
    Created: 5 Jan 2016 10:47:43pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#ifndef LASERCONFIG_H_INCLUDED
#define LASERCONFIG_H_INCLUDED

#include "chuParameters.h"

class LaserConfig : public chuParameterProvider
{
public:
    LaserConfig() : LaserConfig(ValueTree("laserConfig")) {}
    LaserConfig(ValueTree source);

    const int ildaXMin = -32768;
    const int ildaXMax = 32767;
    const int ildaYMin = -32768;
    const int ildaYMax = 32767;
    const int ildaIntensityMin = 0;
    const int ildaIntensityMax = 65535;

    chuParameterInt* pointsPerSecond;
    chuParameterInt* longestUnbrokenLine;
    chuParameterInt* internalDwellPoints;
    chuParameterInt* dwellOffPoints;
    chuParameterInt* dwellOnPoints;
    chuParameterFloat* globalIntensity;
    chuParameterInt* redDelay;
    chuParameterInt* greenDelay;
    chuParameterInt* blueDelay;
    chuParameterBool* flipHorizontal;
    chuParameterBool* flipVertical;
};

class LaserStatistics
{
public:
    float framesPerSecond;
    int pointsPerFrame;
};



#endif  // LASERCONFIG_H_INCLUDED
