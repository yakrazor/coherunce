/*
  ==============================================================================

    LaserConfig.cpp
    Created: 5 Jan 2016 10:47:43pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "LaserConfig.h"

LaserConfig::LaserConfig(ValueTree source)
: chuParameterProvider("Laser Config", source)
{
    addParameter(pointsPerSecond = new chuParameterInt("Points Per Second", 200, 100000, 35000));
    addParameter(longestUnbrokenLine = new chuParameterInt("Longest Unbroken Line", 200, 10000, 1000));
    addParameter(internalDwellPoints = new chuParameterInt("Internal Dwell Points", 0, 50, 3));
    addParameter(dwellOffPoints = new chuParameterInt("Dwell Points (Off)", 0, 50, 10));
    addParameter(dwellOnPoints = new chuParameterInt("Dwell Points (On)", 0, 50, 2));
    addParameter(globalIntensity = new chuParameterFloat("Intensity", 0, 1.0, 0.0));
    addParameter(redDelay = new chuParameterInt("Red Delay", 0, 20, 6));
    addParameter(greenDelay = new chuParameterInt("Green Delay", 0, 20, 6));
    addParameter(blueDelay = new chuParameterInt("Blue Delay", 0, 20, 6));
    addParameter(flipHorizontal = new chuParameterBool("Flip Horizontal", false));
    addParameter(flipVertical = new chuParameterBool("Flip Vertical", false));
}

