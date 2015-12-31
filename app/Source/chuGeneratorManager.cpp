/*
  ==============================================================================

    chuGeneratorManager.cpp
    Created: 30 Dec 2015 3:02:20pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "chuGeneratorManager.h"


void chuGeneratorManager::initialize()
{
    auto pinwheel = new chuGenPolygonPinwheel();
    pinwheel->setActive(true);
    pinwheel->sides->value = 6;
    pinwheel->setOSCAddress("/generator/1");
    allGenerators.add(pinwheel);

    auto pinwheel2 = new chuGenPolygonPinwheel();
    pinwheel2->setActive(false);
    pinwheel2->sides->value = 3;
    pinwheel2->radius->value = 1.0;
    pinwheel2->setOSCAddress("/generator/2");
    allGenerators.add(pinwheel2);

    auto fivePoints = new chuGenFivePoints();
    fivePoints->setActive(false);
    fivePoints->setOSCAddress("/generator/3");
    allGenerators.add(fivePoints);

    auto fivePoints2 = new chuGenFivePoints();
    fivePoints2->setActive(false);
    fivePoints2->setOSCAddress("/generator/4");
    allGenerators.add(fivePoints2);
}

OwnedArray<chuGenerator> chuGeneratorManager::allGenerators;
