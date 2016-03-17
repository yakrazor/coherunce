/*
  ==============================================================================

    chuGenerator.cpp
    Created: 30 Dec 2015 1:32:56pm
    Author:  Michael Dewberry

  ==============================================================================
*/

#include "chuGenerator.h"
#include "chuOSCManager.h"


chuGenerator::chuGenerator(String generatorTypeName, ValueTree source)
: chuParameterProvider(generatorTypeName, source)
{
    addParameter(active = new chuParameterBool("Active", false));
};

bool chuGenerator::isActive() const
{
    return active ? active->getValue() : false;
}

void chuGenerator::setActive(bool b)
{
    if (active) {
        active->setValue(b);
    }
}

void chuGenerator::setName(String name)
{
    chuParameterProvider::setName(name);

    setOSCAddress("/generator/" + name);
}

void chuGenerator::setOSCAddress(const String& addr)
{
    std::vector<chuParameter*> params;
    getParamList(params);
    for (auto& param : params)
    {
        if (chuOSCManager::getReceiver())
        {
            chuOSCManager::getReceiver()->removeListener(param);
            chuOSCManager::getReceiver()->addListener(param, addr + "/param/" + param->getName());
        }
    }
}


