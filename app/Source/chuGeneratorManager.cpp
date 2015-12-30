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
    pinwheel->setOSCAddress("/generator/1");
    allGenerators.add(pinwheel2);
}

OwnedArray<chuGenerator> chuGeneratorManager::allGenerators;
