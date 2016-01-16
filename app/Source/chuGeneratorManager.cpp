/*
  ==============================================================================

    chuGeneratorManager.cpp
    Created: 30 Dec 2015 3:02:20pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "chuGeneratorManager.h"
#include "chuGenPolygonPinwheel.h"
#include "chuGenFivePoints.h"
#include "chuGen16Step.h"


chuGeneratorManager::chuGeneratorManager()
{
    auto pinwheel = new chuGenPolygonPinwheel();
    pinwheel->setActive(false);
    pinwheel->sides->setValue(6);
    pinwheel->radius->setValue(0.75);
    pinwheel->setOSCAddress("/generator/1");
    allGenerators.add(pinwheel);

    auto pinwheel2 = new chuGenPolygonPinwheel();
    pinwheel2->setActive(false);
    pinwheel2->sides->setValue(3);
    pinwheel2->radius->setValue(0.6);
    pinwheel2->color->setValue(Color::fromRGB(255, 0, 255));
    pinwheel2->setOSCAddress("/generator/2");
    allGenerators.add(pinwheel2);

    auto fivePoints = new chuGenFivePoints();
    fivePoints->setActive(false);
    fivePoints->color->setValue(Color::fromRGB(0, 255, 0));
    fivePoints->setOSCAddress("/generator/3");
    allGenerators.add(fivePoints);

    auto fivePoints2 = new chuGenFivePoints();
    fivePoints2->setActive(false);
    fivePoints2->color->setValue(Color::fromRGB(0, 0, 255));
    fivePoints2->setOSCAddress("/generator/4");
    allGenerators.add(fivePoints2);

    auto step = new chuGen16Step();
    step->setActive(false);
    step->setOSCAddress("/generator/5");
    allGenerators.add(step);
}

chuGeneratorManager::~chuGeneratorManager()
{
    allGenerators.clear();
}

void chuGeneratorManager::setCurrentGenerator(chuGenerator* gen)
{
    currentGenerator = gen;
    sendChangeMessage();
}


ScopedPointer<chuGeneratorManager> theManager;

chuGeneratorManager* getGeneratorManager()
{
    if (!theManager)
    {
        theManager = new chuGeneratorManager();
    }
    return theManager;
}

void clearGeneratorManager()
{
    theManager = nullptr;
}