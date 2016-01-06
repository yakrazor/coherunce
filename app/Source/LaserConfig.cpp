/*
  ==============================================================================

    LaserConfig.cpp
    Created: 5 Jan 2016 10:47:43pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "LaserConfig.h"

LaserConfig::LaserConfig()
: pointsPerSecond("Points Per Second", 200, 100000, 30000)
, longestUnbrokenLine("Longest Unbroken Line", 200, 25000, 1000)
, internalDwellPoints("Internal Dwell Points", 0, 50, 1)
, dwellOffPoints("Dwell Points (Off)", 0, 50, 10)
, dwellOnPoints("Dwell Points (On)", 0, 50, 2)
{
}

void LaserConfig::getParamList(std::vector<chuParameter*>& params)
{
    params.push_back(&pointsPerSecond);
    params.push_back(&longestUnbrokenLine);
    params.push_back(&internalDwellPoints);
    params.push_back(&dwellOffPoints);
    params.push_back(&dwellOnPoints);
}
