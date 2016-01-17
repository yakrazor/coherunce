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
#include "chuGenJavascript.h"

#define STRING_BLOCK(...) #__VA_ARGS__

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

    auto js = new chuGenJavascript();
    js->code->setValue(
        "var a = g.getParameter('a');\n"
        "var b = g.getParameter('b');\n"
        "var clk = 1.0 - g.getParameter('barClock');\n"
        "\n"
        "g.addPoint(0,0);\n"
        "g.addPoint(-a, a * b * clk);\n"
        "g.addPoint(-a, -a * b * clk);\n"
        "g.addPoint(a, a * b * clk);\n"
        "g.addPoint(a, -a * b * clk);\n"
        "g.addPoint(0, 0);\n"
    );
    allGenerators.add(js);

    auto js2 = new chuGenJavascript();
    js2->code->setValue(
        "var a = g.getParameter('a');\n"
        "var b = g.getParameter('b');\n"
        "var c = g.getParameter('c');\n"
        "var clk = g.getParameter('barClock');\n"
        "\n"
        "var steps = 16;\n"
        "var k = Math.abs(clk - 0.5);\n"
        "var s = clk * Math.floor(16 * b);\n"
        "var pump = 1.0 - (s - Math.floor(s));\n"
        "\n"
        "for (var t = -1; t <= 1.0; t += 1/steps)\n"
        "{\n"
        "    g.setColor(255, 0, 0);\n"
        "    g.addPoint(t, (a + c * pump) * Math.sin(k * t * Math.PI * 2));\n"
        "    g.setColor(0, 255 * clk, 255 * (1 - clk));\n"
        "    g.addPoint(t, (a + c * pump) * Math.sin(1 - k * t * Math.PI * 2));\n"
        "}\n"
    );
    js2->a->setValue(0.1);
    js2->b->setValue(0.5);
    js2->c->setValue(0.3);
    js2->d->setValue(0.5);

    allGenerators.add(js2);
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