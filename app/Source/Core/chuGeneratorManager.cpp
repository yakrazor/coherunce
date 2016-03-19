/*
  ==============================================================================

    chuGeneratorManager.cpp
    Created: 30 Dec 2015 3:02:20pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "chuGeneratorManager.h"
#include "chuApplication.h"
#include "chuOSCManager.h"

#define STRING_BLOCK(...) #__VA_ARGS__

chuGeneratorManager::chuGeneratorManager()
: currentGenerator(nullptr)
{
    /*
    auto pinwheel = new chuGenPolygonPinwheel();
    pinwheel->setActive(false);
    pinwheel->sides->setValue(6);
    pinwheel->radius->setValue(0.75);
    pinwheel->setOSCAddress("/generator/1");
    allGenerators.push_back(pinwheel);
    getApp()->getCurrentProject()->addGenerator(pinwheel);

    auto pinwheel2 = new chuGenPolygonPinwheel();
    pinwheel2->setActive(false);
    pinwheel2->sides->setValue(3);
    pinwheel2->radius->setValue(0.6);
    pinwheel2->color->setValue(Color::fromRGB(255, 0, 255));
    pinwheel2->setOSCAddress("/generator/2");
    allGenerators.push_back(pinwheel2);
    getApp()->getCurrentProject()->addGenerator(pinwheel2);

    auto fivePoints = new chuGenFivePoints();
    fivePoints->setActive(false);
    fivePoints->color->setValue(Color::fromRGB(0, 255, 0));
    fivePoints->setOSCAddress("/generator/3");
    allGenerators.push_back(fivePoints);
    getApp()->getCurrentProject()->addGenerator(fivePoints);

    auto fivePoints2 = new chuGenFivePoints();
    fivePoints2->setActive(false);
    fivePoints2->color->setValue(Color::fromRGB(0, 0, 255));
    fivePoints2->setOSCAddress("/generator/4");
    allGenerators.push_back(fivePoints2);
    getApp()->getCurrentProject()->addGenerator(fivePoints2);

    auto step = new chuGen16Step();
    step->setActive(false);
    step->setOSCAddress("/generator/5");
    allGenerators.push_back(step);
    getApp()->getCurrentProject()->addGenerator(step);

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
    allGenerators.push_back(js);
    getApp()->getCurrentProject()->addGenerator(js);

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

    allGenerators.push_back(js2);
    getApp()->getCurrentProject()->addGenerator(js2);
     */

    auto recolor = new chuGenRecolorEffect();
    recolor->color1->setValue(Colours::blue);
    recolor->color2->setValue(Colours::green);
    globalEffects.add(recolor);

    auto translate = new chuGenTranslateEffect();
    globalEffects.add(translate);

    auto sinusoid = new chuGenSinusoidEffect();
    globalEffects.add(sinusoid);

    auto noise = new chuGenNoiseEffect();
    globalEffects.add(noise);

    chuOSCManager::getReceiver()->addListener(this, "/currentGenerator/param");
    chuOSCManager::getReceiver()->addListener(this, "/currentGenerator/select");
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

void chuGeneratorManager::deserializeGenerator(String type, ValueTree data)
{
    chuGenerator* newGen = nullptr;
    if (type == "PolygonPinwheel")
    {
        newGen = new chuGenPolygonPinwheel(data);
    }
    else if (type == "FivePoints")
    {
        newGen = new chuGenFivePoints(data);
    }
    else if (type == "Handplane")
    {
        newGen = new chuGenHandplane(data);
    }
    else if (type == "CustomJavascript")
    {
        newGen = new chuGenJavascript(data);
    }
    else if (type == "PolygonPinwheel")
    {
        newGen = new chuGenPolygonPinwheel(data);
    }
    else if (type == "16Step")
    {
        newGen = new chuGen16Step(data);
    }

    if (newGen)
    {
        addGenerator(newGen);
    }
    else
    {
        // TODO: warn on unexpected generator type
    }
}

void chuGeneratorManager::addGenerator(chuGenerator* newGen)
{
    allGenerators.add(newGen);
}

void chuGeneratorManager::deleteGenerator(chuGenerator* genToDelete)
{
    if (genToDelete == currentGenerator)
    {
        setCurrentGenerator(nullptr);
    }
    allGenerators.removeObject(genToDelete);
}

void chuGeneratorManager::renameGenerator(chuGenerator* gen, const String& newName)
{
    gen->setName(newName);
    sendChangeMessage();
}


void chuGeneratorManager::oscMessageReceived(const OSCMessage& message)
{
    if (message.getAddressPattern() == "/currentGenerator/select")
    {
        OSCArgument* arg = message.begin();
        if (!arg || !arg->isInt32())
        {
            return;
        }

        int generatorIndex = arg->getInt32();

        for (int i = 0; i < allGenerators.size(); i++)
        {
            allGenerators[i]->setActive(i == generatorIndex);
        }
        sendChangeMessage();
    }
    else if (message.getAddressPattern() == "/currentGenerator/param")
    {
        if (!currentGenerator) {
            return;
        }

        OSCArgument* arg = message.begin();
        if (!arg || !arg->isInt32())
        {
            return;
        }

        int paramIndex = arg->getInt32();

        arg++;

        if (!arg || !arg->isFloat32())
        {
            return;
        }

        float rawValue = arg->getFloat32();

        std::vector<chuParameter*> params;
        currentGenerator->getParamList(params);
        int index = 0;
        for (auto param : params)
        {
            chuParameterFloat* floatParam = dynamic_cast<chuParameterFloat*>(param);
            if (floatParam)
            {
                if (index == paramIndex)
                {
                    floatParam->setValue(floatParam->getMinValue() +
                                         rawValue * (floatParam->getMaxValue() - floatParam->getMinValue()));
                    return;
                }
                else
                {
                    index++;
                    continue;
                }
            }

            chuParameterInt* intParam = dynamic_cast<chuParameterInt*>(param);
            if (intParam)
            {
                if (index == paramIndex)
                {
                    intParam->setValue(intParam->getMinValue() +
                                         rawValue * (intParam->getMaxValue() - intParam->getMinValue()));
                    return;
                }
                else
                {
                    index++;
                    continue;
                }
            }

            chuParameterColor* colorParam = dynamic_cast<chuParameterColor*>(param);
            if (colorParam)
            {
                if (index == paramIndex)
                {
                    colorParam->setHue(rawValue);
                    return;
                }
                else
                {
                    index++;
                    continue;
                }
            }
        }
    }
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

